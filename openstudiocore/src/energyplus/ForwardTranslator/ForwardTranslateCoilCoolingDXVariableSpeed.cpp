/**********************************************************************
 *  Copyright (c) 2008-2015, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#include "../ForwardTranslator.hpp"
#include "../../model/Model.hpp"
#include "../../model/CoilCoolingDXVariableSpeed.hpp"
#include "../../model/CoilCoolingDXVariableSpeedSpeedData.hpp"
#include "../../model/Node.hpp"
#include "../../model/Curve.hpp"
#include "../../model/Schedule.hpp"
#include <utilities/idd/Coil_Cooling_DX_VariableSpeed_FieldEnums.hxx>
#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>
#include "../../utilities/idf/IdfExtensibleGroup.hpp"

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateCoilCoolingDXVariableSpeed( CoilCoolingDXVariableSpeed & modelObject )
{
  boost::optional<std::string> s;
  boost::optional<double> value;

  // Name
  IdfObject idfObject = createRegisterAndNameIdfObject(openstudio::IddObjectType::Coil_Cooling_DX_VariableSpeed, modelObject);

  // IndoorAirInletNodeName
  if( auto node = modelObject.inletModelObject() ) {
    idfObject.setString(Coil_Cooling_DX_VariableSpeedFields::IndoorAirInletNodeName,node->name().get());
  }  

  // IndoorAirOutletNodeName
  if( auto node = modelObject.outletModelObject() ) {
    idfObject.setString(Coil_Cooling_DX_VariableSpeedFields::IndoorAirOutletNodeName,node->name().get());
  }

  // NominalSpeedLevel
  if( auto speedLevel = modelObject.nominalSpeedLevel() ) {
    idfObject.setInt(Coil_Cooling_DX_VariableSpeedFields::NominalSpeedLevel,speedLevel);
  }

  // GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel
  if( modelObject.isGrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevelAutosized() ) {
    idfObject.setString(Coil_Cooling_DX_VariableSpeedFields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel,"AutoSize");
  } else if( (value = modelObject.grossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel()) ) {
    idfObject.setDouble(Coil_Cooling_DX_VariableSpeedFields::GrossRatedTotalCoolingCapacityAtSelectedNominalSpeedLevel,value.get());
  }

  // RatedAirFlowRateAtSelectedNominalSpeedLevel
  if( modelObject.isRatedAirFlowRateAtSelectedNominalSpeedLevelAutosized() ) {
    idfObject.setString(Coil_Cooling_DX_VariableSpeedFields::RatedAirFlowRateAtSelectedNominalSpeedLevel,"AutoSize");
  } else if( (value = modelObject.ratedAirFlowRateAtSelectedNominalSpeedLevel()) ) {
    idfObject.setDouble(Coil_Cooling_DX_VariableSpeedFields::RatedAirFlowRateAtSelectedNominalSpeedLevel,value.get());
  }

  // NominalTimeforCondensatetoBeginLeavingtheCoil
  if( (value = modelObject.nominalTimeforCondensatetoBeginLeavingtheCoil()) ) {
    idfObject.setDouble(Coil_Cooling_DX_VariableSpeedFields::NominalTimeforCondensatetoBeginLeavingtheCoil,value.get());
  }

  // InitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity
  if( (value = modelObject.initialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity()) ) {
    idfObject.setDouble(Coil_Cooling_DX_VariableSpeedFields::InitialMoistureEvaporationRateDividedbySteadyStateACLatentCapacity,value.get());
  }

  // EnergyPartLoadFractionCurveName
  { 
    auto curve = modelObject.energyPartLoadFractionCurve();
    if( auto _curve = translateAndMapModelObject(curve) ) {
      idfObject.setString(Coil_Cooling_DX_VariableSpeedFields::EnergyPartLoadFractionCurveName,_curve->name().get());
    }
  }

  // CondenserAirInletNodeName

  // CondenserType
  if( (s = modelObject.condenserType()) ) {
    idfObject.setString(Coil_Cooling_DX_VariableSpeedFields::CondenserType,s.get());
  }

  // EvaporativeCondenserPumpRatedPowerConsumption
  if( modelObject.isEvaporativeCondenserPumpRatedPowerConsumptionAutosized() ) {
    idfObject.setString(Coil_Cooling_DX_VariableSpeedFields::EvaporativeCondenserPumpRatedPowerConsumption,"AutoSize");
  } else if( (value = modelObject.evaporativeCondenserPumpRatedPowerConsumption()) ) {
    idfObject.setDouble(Coil_Cooling_DX_VariableSpeedFields::EvaporativeCondenserPumpRatedPowerConsumption,value.get());
  }

  // CrankcaseHeaterCapacity
  if( (value = modelObject.crankcaseHeaterCapacity()) ) {
    idfObject.setDouble(Coil_Cooling_DX_VariableSpeedFields::CrankcaseHeaterCapacity,value.get());
  }

  // MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation
  if( (value = modelObject.maximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation()) ) {
    idfObject.setDouble(Coil_Cooling_DX_VariableSpeedFields::MaximumOutdoorDryBulbTemperatureforCrankcaseHeaterOperation,value.get());
  }

  // SupplyWaterStorageTankName

  // CondensateCollectionWaterStorageTankName

  // BasinHeaterCapacity
  if( (value = modelObject.basinHeaterCapacity()) ) {
    idfObject.setDouble(Coil_Cooling_DX_VariableSpeedFields::BasinHeaterCapacity,value.get());
  }
  
  // BasinHeaterSetpointTemperature
  if( (value = modelObject.basinHeaterSetpointTemperature()) ) {
    idfObject.setDouble(Coil_Cooling_DX_VariableSpeedFields::BasinHeaterSetpointTemperature,value.get());
  }
  
  // BasinHeaterOperatingScheduleName
  if( auto schedule = modelObject.basinHeaterOperatingSchedule() ) {
    if( auto _schedule = translateAndMapModelObject(schedule.get()) ) {
      idfObject.setString(Coil_Cooling_DX_VariableSpeedFields::BasinHeaterOperatingScheduleName,_schedule->name().get());
    }
  }
  
  // NumberofSpeeds
  if( auto num = modelObject.speeds().size() ) {
    idfObject.setInt(Coil_Cooling_DX_VariableSpeedFields::NumberofSpeeds,num);
  }

  for( auto speed: modelObject.speeds() ) {
    auto eg = idfObject.pushExtensibleGroup();

    // SpeedReferenceUnitGrossRatedTotalCoolingCapacity
    if( (value = speed.referenceUnitGrossRatedTotalCoolingCapacity()) ) {
      eg.setDouble(Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedReferenceUnitGrossRatedTotalCoolingCapacity,value.get());
    }

    // SpeedReferenceUnitGrossRatedSensibleHeatRatio
    if( (value = speed.referenceUnitGrossRatedSensibleHeatRatio()) ) {
      eg.setDouble(Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedReferenceUnitGrossRatedSensibleHeatRatio,value.get());
    }

    // SpeedReferenceUnitGrossRatedCoolingCOP
    if( (value = speed.referenceUnitGrossRatedCoolingCOP()) ) {
      eg.setDouble(Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedReferenceUnitGrossRatedCoolingCOP,value.get());
    }

    // SpeedReferenceUnitRatedAirFlowRate
    if( (value = speed.referenceUnitRatedAirFlowRate()) ) {
      eg.setDouble(Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedReferenceUnitRatedAirFlowRate,value.get());
    }

    // SpeedReferenceUnitRatedCondenserAirFlowRate
    if( (value = speed.referenceUnitRatedCondenserAirFlowRate()) ) {
      eg.setDouble(Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedReferenceUnitRatedCondenserAirFlowRate,value.get());
    }

    // SpeedReferenceUnitRatedPadEffectivenessofEvapPrecooling
    if( (value = speed.referenceUnitRatedPadEffectivenessofEvapPrecooling()) ) {
      eg.setDouble(Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedReferenceUnitRatedPadEffectivenessofEvapPrecooling,value.get());
    }

    // SpeedTotalCoolingCapacityFunctionofTemperatureCurveName
    { 
      auto curve = speed.totalCoolingCapacityFunctionofTemperatureCurve();
      if( auto _curve = translateAndMapModelObject(curve) ) {
        eg.setString(Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedTotalCoolingCapacityFunctionofTemperatureCurveName,_curve->name().get());
      }
    }

    // SpeedTotalCoolingCapacityFunctionofAirFlowFractionCurveName
    { 
      auto curve = speed.totalCoolingCapacityFunctionofAirFlowFractionCurve();
      if( auto _curve = translateAndMapModelObject(curve) ) {
        eg.setString(Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedTotalCoolingCapacityFunctionofAirFlowFractionCurveName,_curve->name().get());
      }
    }

    // SpeedEnergyInputRatioFunctionofTemperatureCurveName
    { 
      auto curve = speed.energyInputRatioFunctionofTemperatureCurve();
      if( auto _curve = translateAndMapModelObject(curve) ) {
        eg.setString(Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedEnergyInputRatioFunctionofTemperatureCurveName,_curve->name().get());
      }
    }

    // SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName
    { 
      auto curve = speed.energyInputRatioFunctionofAirFlowFractionCurve();
      if( auto _curve = translateAndMapModelObject(curve) ) {
        eg.setString(Coil_Cooling_DX_VariableSpeedExtensibleFields::SpeedEnergyInputRatioFunctionofAirFlowFractionCurveName,_curve->name().get());
      }
    }
  
  }

  return idfObject;
}

} // energyplus

} // openstudio

