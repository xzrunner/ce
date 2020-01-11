#pragma once

#include "cga/Function.h"

namespace cga
{
namespace func
{

class Print : public Function
{
public:
    virtual VarPtr Eval(const std::vector<VarPtr>& parms,
        const std::vector<GeoPtr>& geos, std::ostream& console) const override;

private:
    static void PrintVar(const VarPtr& var, const std::vector<GeoPtr>& geos, std::ostream& console);

}; // Print

}
}