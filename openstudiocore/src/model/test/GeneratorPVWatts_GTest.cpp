/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) 2008-2018, Alliance for Sustainable Energy, LLC. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 *  following conditions are met:
 *
 *  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *  disclaimer.
 *
 *  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *  following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote
 *  products derived from this software without specific prior written permission from the respective party.
 *
 *  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative
 *  works may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without
 *  specific prior written permission from Alliance for Sustainable Energy, LLC.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER, THE UNITED STATES GOVERNMENT, OR ANY CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **********************************************************************************************************************/

#include <gtest/gtest.h>
#include <string>

#include "ModelFixture.hpp"

#include "../Model.hpp"
#include "../Model_Impl.hpp"

#include "../GeneratorPVWatts.hpp"
#include "../GeneratorPVWatts_Impl.hpp"
#include "../Surface.hpp"
#include "../Surface_Impl.hpp"
#include "../ShadingSurface.hpp"
#include "../ShadingSurface_Impl.hpp"
#include "../ElectricLoadCenterDistribution.hpp"
#include "../ElectricLoadCenterDistribution_Impl.hpp"

using namespace openstudio::model;
using namespace openstudio;

TEST_F(ModelFixture, GeneratorPVWatts_GeneratorPVWatts) {
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  ASSERT_EXIT(
  {
    // create a model to use
    Model model;

    // create a foundation kiva object to use
    GeneratorPVWatts generator(model, 1);

    exit(0);
  },
    ::testing::ExitedWithCode(0),
    ""
    );

  // create a model to use
  Model model;

  // create a pvwatts generator to use
  GeneratorPVWatts generator(model, 1);

  EXPECT_TRUE(generator.isModuleTypeDefaulted());
  EXPECT_TRUE(generator.isArrayTypeDefaulted());
  EXPECT_TRUE(generator.isSystemLossesDefaulted());
  EXPECT_TRUE(generator.isTiltAngleDefaulted());
  EXPECT_TRUE(generator.isAzimuthAngleDefaulted());
  EXPECT_TRUE(generator.isGroundCoverageRatioDefaulted());

  ASSERT_EQ("", generator.pvWattsVersion());
  ASSERT_EQ(1, generator.dcSystemCapacity());
  ASSERT_EQ("Standard", generator.moduleType());
  ASSERT_EQ("FixedOpenRack", generator.arrayType());
  ASSERT_EQ(0.14, generator.systemLosses());
  ASSERT_EQ(20, generator.tiltAngle());
  ASSERT_EQ(180, generator.azimuthAngle());
  ASSERT_EQ(0.4, generator.groundCoverageRatio());
  
}

// test setting and getting
TEST_F(ModelFixture, GeneratorPVWatts_SetGetFields) {

}

// test constructing with a surface
TEST_F(ModelFixture, GeneratorPVWatts_SurfaceConstruct) {
  Model model;
  Point3dVector points;
  points.clear();
  points.push_back(Point3d(0, 2, 0));
  points.push_back(Point3d(0, 0, 0));
  points.push_back(Point3d(1, 0, 0));
  Surface surface(points, model);
  GeneratorPVWatts generator(model, surface, 1);
  EXPECT_TRUE(generator.surface());
  generator.resetSurface();
  EXPECT_FALSE(generator.surface());
}

// test assigning a surface
TEST_F(ModelFixture, GeneratorPVWatts_SurfaceAssign) {
  Model model;
  GeneratorPVWatts generator(model, 1);
  EXPECT_FALSE(generator.surface());
  Point3dVector points;
  points.clear();
  points.push_back(Point3d(0, 2, 0));
  points.push_back(Point3d(0, 0, 0));
  points.push_back(Point3d(1, 0, 0));
  ShadingSurface shadingsurface(points, model);
  generator.setSurface(shadingsurface);
  EXPECT_TRUE(generator.surface());
  boost::optional<PlanarSurface> optsurface = generator.surface();
  // ShadingSurface shadingsurface = optsurface.get().cast<ShadingSurface>();
  // shadingsurface.remove();
  // EXPECT_FALSE(generator.surface());
}

// test cloning it

// test that remove works

// test electric load center distribution