#include "utility.h"

#include <cga/node/Extrude.h>
#include <cga/node/PrimCube.h>
#include <cga/node/PrimQuad.h>

#include <cga/EvalNode.h>

#include <catch/catch.hpp>

TEST_CASE("extrude")
{
    test::init();

    cga::EvalNode eval;

    auto quad = std::make_shared<cga::node::PrimQuad>();
    quad->SetLength(1);
    quad->SetWidth(2);
    eval.AddNode(quad);

    auto extrude = std::make_shared<cga::node::Extrude>();
    extrude->SetDistance(3);
    eval.AddNode(extrude);

    eval.Connect({ quad, 0 }, { extrude, 0 });

    auto geos = eval.Eval();

    auto geo = test::query_geo(geos, extrude);
    test::check_points_num(*geo, 8);
    test::check_faces_num(*geo, 6);
#ifdef BUILD_CENTER
    test::check_aabb(*geo, { -1, 0, -0.5f }, { 1, 3, 0.5f });
#else
    test::check_aabb(*geo, { 0, 0, 0 }, { 2, 3, 1 });
#endif // BUILD_CENTER
}

TEST_CASE("cube")
{
    test::init();

    cga::EvalNode eval;

    auto cube = std::make_shared<cga::node::PrimCube>();
    cube->SetWidth(1);
    cube->SetHeight(2);
    cube->SetDepth(3);
    eval.AddNode(cube);

    auto geos = eval.Eval();

    auto geo = test::query_geo(geos, cube);
#ifdef BUILD_CENTER
    test::check_aabb(*geo, { -0.5f, -1, -1.5f }, { 0.5f, 1, 1.5f });
#else
    test::check_aabb(*geo, { 0, 0, 0 }, { 1, 2, 3 });
#endif // BUILD_CENTER
}

TEST_CASE("quad")
{
    test::init();

    cga::EvalNode eval;

    auto quad = std::make_shared<cga::node::PrimQuad>();
    quad->SetWidth(1);
    quad->SetLength(2);
    eval.AddNode(quad);

    auto geos = eval.Eval();

    auto geo = test::query_geo(geos, quad);
#ifdef BUILD_CENTER
    test::check_aabb(*geo, { -0.5f, 0, -1 }, { 0.5f, 0, 1 });
#else
    test::check_aabb(*geo, { 0, 0, 0 }, { 1, 0, 2 });
#endif // BUILD_CENTER
}