/*
 * (C) Copyright 2019 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "ufo/filters/obsfunctions/ObsFunctionLNVD.h"

#include <math.h>
#include <vector>

#include "ioda/ObsDataVector.h"
#include "oops/util/missingValues.h"
#include "ufo/filters/Variable.h"

namespace ufo {

static ObsFunctionMaker<ObsFunctionLNVD> makerObsFuncLNVD_("LNVD");

// -----------------------------------------------------------------------------

ObsFunctionLNVD::ObsFunctionLNVD(const eckit::LocalConfiguration conf)
  : invars_(), group_() {
  group_ = conf.getString("type", "ObsValue");
  invars_ += Variable("eastward_wind@" + group_);
  invars_ += Variable("northward_wind@" + group_);

  groupg_ = conf.getString("type", "GsiHofX");
  invars_ += Variable("eastward_wind@" + groupg_);
  invars_ += Variable("northward_wind@" + groupg_);
}

// -----------------------------------------------------------------------------

ObsFunctionLNVD::~ObsFunctionLNVD() {}

// -----------------------------------------------------------------------------

void ObsFunctionLNVD::compute(const ObsFilterData & in,
                                  ioda::ObsDataVector<float> & out) const {
  // TODO(AS): should use constants for variable names
  const size_t nlocs = in.nlocs();
  const float missing = util::missingValue(missing);
  std::vector<float> u, v, ug, vg;
  in.get(Variable("eastward_wind@" + group_), u);
  in.get(Variable("northward_wind@" + group_), v);
  in.get(Variable("eastward_wind@" + groupg_), ug);
  in.get(Variable("northward_wind@" + groupg_), vg);
  for (size_t jj = 0; jj < nlocs; ++jj) {
    if (u[jj] != missing && v[jj] != missing && ug[jj] != missing && vg[jj] != missing) {
      out[0][jj] = sqrt((u[jj]-ug[jj])*(u[jj]-ug[jj]) + (v[jj]-vg[jj])*(v[jj]-vg[jj])) 
                    / log(sqrt(u[jj]*u[jj] + v[jj]*v[jj]));

      oops::Log::debug() << "u, v, ug, vg: " << u[jj]  << ", " << v[jj]  << ", " 
                                             << ug[jj] << ", " << vg[jj] << std::endl;
                                                  
      oops::Log::debug() << "LNVD: " << out[0][jj] << std::endl;
    } else {
      out[0][jj] = missing;
      oops::Log::debug() << "u and v, or ug and vg, are missing at index, " << jj << std::endl;
    }
  }
}

// -----------------------------------------------------------------------------

const ufo::Variables & ObsFunctionLNVD::requiredVariables() const {
  return invars_;
}

// -----------------------------------------------------------------------------

}  // namespace ufo
