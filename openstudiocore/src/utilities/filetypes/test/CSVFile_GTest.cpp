/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2019, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#include <gtest/gtest.h>

#include "../CSVFile.hpp"
#include "../../data/Variant.hpp"

#include <resources.hxx>

using namespace openstudio;

TEST(Filetypes, CSVFile_New) 
{
  CSVFile csvFile;
  EXPECT_EQ(0, csvFile.numRows());
  EXPECT_EQ(0, csvFile.numColumns());

  auto rows = csvFile.rows();
  EXPECT_EQ(0, rows.size());

  std::vector<Variant> row;

  row.push_back(Variant(1));
  csvFile.addRow(row);

  row.clear();
  row.push_back(Variant(1));
  row.push_back(Variant(2.2));
  csvFile.addRow(row);
  
  row.clear();
  row.push_back(Variant(1));
  row.push_back(Variant(2.2));
  row.push_back(Variant(0.33));
  csvFile.addRow(row); 

  ASSERT_EQ(3, csvFile.numRows());
  ASSERT_EQ(3, csvFile.numColumns());

  rows = csvFile.rows();
  for (const auto& r : rows) {
    ASSERT_EQ(csvFile.numColumns(), r.size());
  }

  // row 1
  EXPECT_EQ(VariantType::Integer, rows[0][0].variantType().value());
  EXPECT_EQ(1, rows[0][0].valueAsInteger());
  EXPECT_EQ("1", rows[0][0].valueAsString());

  EXPECT_EQ(VariantType::String, rows[0][1].variantType().value());
  EXPECT_EQ("", rows[0][1].valueAsString());

  EXPECT_EQ(VariantType::String, rows[0][2].variantType().value());
  EXPECT_EQ("", rows[0][2].valueAsString());

  // row 2
  EXPECT_EQ(VariantType::Integer, rows[1][0].variantType().value());
  EXPECT_EQ(1, rows[1][0].valueAsInteger());
  EXPECT_EQ("1", rows[1][0].valueAsString());

  EXPECT_EQ(VariantType::Double, rows[1][1].variantType().value());
  EXPECT_EQ(2.2, rows[1][1].valueAsInteger());
  EXPECT_EQ("2.2", rows[1][1].valueAsString());

  EXPECT_EQ(VariantType::String, rows[1][2].variantType().value());
  EXPECT_EQ("", rows[1][2].valueAsString());

  // row 3
  EXPECT_EQ(VariantType::Integer, rows[2][0].variantType().value());
  EXPECT_EQ(1, rows[2][0].valueAsInteger());
  EXPECT_EQ("1", rows[2][0].valueAsString());

  EXPECT_EQ(VariantType::Double, rows[2][1].variantType().value());
  EXPECT_EQ(2.2, rows[1][1].valueAsDouble());
  EXPECT_EQ("2.2", rows[1][1].valueAsString());

  EXPECT_EQ(VariantType::Double, rows[2][2].variantType().value());
  EXPECT_EQ(0.33, rows[2][2].valueAsDouble());
  EXPECT_EQ("0.33", rows[2][2].valueAsString());

}

TEST(Filetypes, CSVFile_Load)
{
  path p = resourcesPath() / toPath("utilities/Filetypes/test_csv.csv");
  path p2 = resourcesPath() / toPath("utilities/Filetypes/TDV_2008_kBtu_CZ13.csv");
  path p3 = resourcesPath() / toPath("utilities/Filetypes/USA_CO_Golden-NREL.724666_TMY3.epw");
  path p4 = resourcesPath() / toPath("utilities/Filetypes/min.osw");

  boost::optional<CSVFile> csvFile;
  
  // test_csv.csv
  csvFile = CSVFile::load(p);
  ASSERT_TRUE(csvFile);
  ASSERT_EQ(8u, csvFile->numRows());
  ASSERT_EQ(3u, csvFile->numColumns());
  auto rows = csvFile->rows();
  for (const auto& row : rows) {
    ASSERT_EQ(csvFile->numColumns(), row.size());
  }

  // row 1
  EXPECT_EQ(VariantType::Integer, rows[0][0].variantType().value());
  EXPECT_EQ(1, rows[0][0].valueAsInteger());
  EXPECT_EQ("1", rows[0][0].valueAsString());

  EXPECT_EQ(VariantType::Integer, rows[0][1].variantType().value());
  EXPECT_EQ(2, rows[0][1].valueAsInteger());
  EXPECT_EQ("2", rows[0][1].valueAsString());

  EXPECT_EQ(VariantType::Integer, rows[0][2].variantType().value());
  EXPECT_EQ(3, rows[0][2].valueAsInteger());
  EXPECT_EQ("3", rows[0][2].valueAsString()); 

  // row 2
  EXPECT_EQ(VariantType::String, rows[1][0].variantType().value());
  EXPECT_EQ("", rows[1][0].valueAsString());

  EXPECT_EQ(VariantType::String, rows[1][1].variantType().value());
  EXPECT_EQ("A CSV File", rows[1][1].valueAsString());

  EXPECT_EQ(VariantType::String, rows[1][2].variantType().value());
  EXPECT_EQ("", rows[1][2].valueAsString());

  // row 3
  EXPECT_EQ(VariantType::String, rows[2][0].variantType().value());
  EXPECT_EQ("", rows[2][0].valueAsString());

  EXPECT_EQ(VariantType::String, rows[2][1].variantType().value());
  EXPECT_EQ("", rows[2][1].valueAsString());

  EXPECT_EQ(VariantType::String, rows[2][2].variantType().value());
  EXPECT_EQ("CSV, File", rows[2][2].valueAsString()); 

  // row 4
  EXPECT_EQ(VariantType::String, rows[3][0].variantType().value());
  EXPECT_EQ("", rows[3][0].valueAsString());

  EXPECT_EQ(VariantType::String, rows[3][1].variantType().value());
  EXPECT_EQ("", rows[3][1].valueAsString());

  EXPECT_EQ(VariantType::String, rows[3][2].variantType().value());
  EXPECT_EQ("", rows[3][2].valueAsString());

  // row 5
  EXPECT_EQ(VariantType::String, rows[4][0].variantType().value());
  EXPECT_EQ("A", rows[4][0].valueAsString());

  EXPECT_EQ(VariantType::String, rows[4][1].variantType().value());
  EXPECT_EQ("", rows[4][1].valueAsString());

  EXPECT_EQ(VariantType::String, rows[4][2].variantType().value());
  EXPECT_EQ("", rows[4][2].valueAsString());

  // row 6
  EXPECT_EQ(VariantType::String, rows[5][0].variantType().value());
  EXPECT_EQ("A", rows[5][0].valueAsString());

  EXPECT_EQ(VariantType::String, rows[5][1].variantType().value());
  EXPECT_EQ("B", rows[5][1].valueAsString());

  EXPECT_EQ(VariantType::String, rows[5][2].variantType().value());
  EXPECT_EQ("", rows[5][2].valueAsString());

  // row 7
  EXPECT_EQ(VariantType::String, rows[6][0].variantType().value());
  EXPECT_EQ("A", rows[6][0].valueAsString());

  EXPECT_EQ(VariantType::String, rows[6][1].variantType().value());
  EXPECT_EQ("B", rows[6][1].valueAsString());

  EXPECT_EQ(VariantType::String, rows[6][2].variantType().value());
  EXPECT_EQ("C", rows[6][2].valueAsString());

  // row 8
  EXPECT_EQ(VariantType::String, rows[7][0].variantType().value());
  EXPECT_EQ("", rows[7][0].valueAsString());

  EXPECT_EQ(VariantType::String, rows[7][1].variantType().value());
  EXPECT_EQ("", rows[7][1].valueAsString());

  EXPECT_EQ(VariantType::String, rows[7][2].variantType().value());
  EXPECT_EQ("", rows[7][2].valueAsString());


  // more files
  csvFile = CSVFile::load(p2);
  ASSERT_TRUE(csvFile);

  csvFile = CSVFile::load(p3);
  ASSERT_TRUE(csvFile);

  csvFile = CSVFile::load(p4);
  EXPECT_FALSE(csvFile);
}
