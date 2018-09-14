/*
 * (C) Copyright 2017-2018 UCAR
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 */

// TODO(anyone): through the file replace ObsExample with <Your_Obs_Operator_Name>
#include "ufo/example/ObsExample.h"

#include <ostream>
#include <string>
#include <vector>

#include "ioda/ObsVector.h"

#include "oops/base/Variables.h"

#include "ufo/GeoVaLs.h"
#include "ufo/ObsBias.h"

namespace ufo {

// -----------------------------------------------------------------------------

ObsExample::ObsExample(const ioda::ObsSpace & odb, const eckit::Configuration & config)
  : keyOper_(0), varin_(), odb_(odb)
{
  const eckit::Configuration * configc = &config;
  // TODO(anyone): replace ufo_example_setup_f90 with the call to your Fortran routine
  //       to setup obs operator (defined in ObsExample.interface.F90)
  ufo_example_setup_f90(keyOper_, &configc);
  // TODO(anyone): list the variables for GeoVaLs that are needed for the observation
  //       operator below in vv (e.g., vv{"temperature", "humidity"})
  const std::vector<std::string> vv{""};
  varin_.reset(new oops::Variables(vv));
  oops::Log::trace() << "ObsExample created." << std::endl;
}

// -----------------------------------------------------------------------------

ObsExample::~ObsExample() {
  // TODO(anyone): replace ufo_example_delete_f90 with the call to your Fortran routine
  //       to destruct observation operator (defined in ObsExample.interface.F90)
  ufo_example_delete_f90(keyOper_);
  oops::Log::trace() << "ObsExample destructed" << std::endl;
}

// -----------------------------------------------------------------------------

void ObsExample::simulateObs(const GeoVaLs & gv, ioda::ObsVector & ovec,
                                  const ObsBias & bias) const {
  // TODO(anyone): replace ufo_example_eqv_f90 with the call to your Fortran routine
  //       to apply observation operator (defined in ObsExample.interface.F90)

  ufo_example_eqv_f90(keyOper_, gv.toFortran(), odb_.toFortran(), ovec.toFortran(),
                      bias.toFortran());
  oops::Log::trace() << "ObsExample: observation operator run" << std::endl;
}

// -----------------------------------------------------------------------------

void ObsExample::print(std::ostream & os) const {
  os << "ObsExample::print not implemented";
}

// -----------------------------------------------------------------------------

}  // namespace ufo
#endif  // UFO_OBSEXAMPLE_H_
