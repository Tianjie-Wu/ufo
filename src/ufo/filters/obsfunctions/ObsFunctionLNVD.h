/*
 * (C) Copyright 2019 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef UFO_FILTERS_OBSFUNCTIONS_OBSFUNCTIONVELOCITY_H_
#define UFO_FILTERS_OBSFUNCTIONS_OBSFUNCTIONVELOCITY_H_

#include <string>

#include "ufo/filters/ObsFilterData.h"
#include "ufo/filters/obsfunctions/ObsFunctionBase.h"
#include "ufo/filters/Variables.h"

namespace ufo {

// -----------------------------------------------------------------------------

class ObsFunctionLNVD : public ObsFunctionBase {
 public:
  explicit ObsFunctionLNVD(const eckit::LocalConfiguration);
  ~ObsFunctionLNVD();

  void compute(const ObsFilterData &,
               ioda::ObsDataVector<float> &) const;
  const ufo::Variables & requiredVariables() const;
 private:
  ufo::Variables invars_;
  std::string group_;
  std::string groupg_;
};

// -----------------------------------------------------------------------------

}  // namespace ufo

#endif  // UFO_FILTERS_OBSFUNCTIONS_OBSFUNCTIONVELOCITY_H_
