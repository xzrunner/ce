#include "archgraph/op/Color.h"
#include "archgraph/Geometry.h"
#include "archgraph/EvalExpr.h"
#include "archgraph/EvalContext.h"
#include "archgraph/Variant.h"

#include <polymesh3/Polytope.h>

namespace archgraph
{
namespace op
{

void Color::Execute(const std::vector<GeoPtr>& in, std::vector<GeoPtr>& out,
                    const EvalContext& ctx)
{
    if (in.empty() || !in[0]) {
        out.resize(1, nullptr);
        return;
    }

    assert(in.size() == 1);
    auto geo = std::make_shared<Geometry>(*in[0]);
    geo->SetColor(m_color);
    out.push_back(geo);
}

void Color::Setup(const std::vector<cga::ExprNodePtr>& parms,
                  const Rule::CompoundSel& selectors, const EvalContext& ctx)
{
    assert(!parms.empty() && selectors.sels.empty());
    if (parms.size() == 1)
    {
        auto var = EvalExpr::Eval(parms[0], ctx);
        SetColor(StringToColor(check_string(var)));
    }
    else if (parms.size() == 3)
    {
        sm::vec3 col;
        for (size_t i = 0; i < 3; ++i) {
            auto var = EvalExpr::Eval(parms[i], ctx);
            col.xyz[i] = check_float(var);
        }
        SetColor(col);
    }
    else
    {
        assert(0);
    }
}

sm::vec3 Color::StringToColor(const std::string& str)
{
    assert(str.size() == 7 && str[0] == '#');

    auto to_int = [](char c) -> int {
        if (c >= '0' && c <= '9') {
            return c - '0';
        } else if (c >= 'A' && c <= 'F') {
            return c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
            return c - 'a' + 10;
        } else {
            assert(0);
            return 0;
        }
    };

    auto to_flt = [&](char h, char l) -> float {
        return (to_int(h) * 16 + to_int(l)) / 255.0f;
    };

    sm::vec3 col;
    col.x = to_flt(str[1], str[2]);
    col.y = to_flt(str[3], str[4]);
    col.z = to_flt(str[5], str[6]);
    return col;
}

}
}