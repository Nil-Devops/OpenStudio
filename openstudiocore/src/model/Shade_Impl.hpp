/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2018, Alliance for Sustainable Energy, LLC. All rights reserved.
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

#ifndef MODEL_SHADE_IMPL_HPP
#define MODEL_SHADE_IMPL_HPP

#include "ModelAPI.hpp"
#include "ShadingMaterial_Impl.hpp"

#include "../utilities/units/Quantity.hpp"
#include "../utilities/units/OSOptionalQuantity.hpp"

namespace openstudio {
namespace model {

namespace detail {

  /** Shade_Impl is a ShadingMaterial_Impl that is the implementation class for Shade.*/
  class MODEL_API Shade_Impl : public ShadingMaterial_Impl {
































































    // TODO: Add relationships for objects related to this one, but not pointed to by the underlying data.
    //       Such relationships can be generated by the GenerateRelationships.rb script.
   public:
    /** @name Constructors and Destructors */
    //@{

    Shade_Impl(const IdfObject& idfObject,
               Model_Impl* model,
               bool keepHandle);

    Shade_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
               Model_Impl* model,
               bool keepHandle);

    Shade_Impl(const Shade_Impl& other,
               Model_Impl* model,
               bool keepHandle);

    virtual ~Shade_Impl() {}

    //@}

    /** @name Virtual Methods */
    //@{

    virtual const std::vector<std::string>& outputVariableNames() const override;

    virtual IddObjectType iddObjectType() const override;

    //@}
    /** @name Getters */
    //@{

    /** Get the thickness of the material. Note that the construction may need to add additional
     *  thickness for an air gap, depending on context. */
    virtual double thickness() const override;

    /** The conductivitiy of the material in W/m*K. */
    double thermalConductivity() const;

    /** The conductance of the material in W/m^2*K. */
    double thermalConductance() const;

    /** The resistivity of the material in m*K/W. */
    double thermalResistivity() const;

    /** The resistance of the material in m^2*K/W. */
    double thermalResistance() const;

    double thermalTransmittance() const;

    double solarTransmittance() const;

    double solarAbsorptance() const;

    double solarReflectance() const;

    double visibleAbsorptance() const;

    virtual boost::optional<double> interiorVisibleAbsorptance() const override;

    virtual boost::optional<double> exteriorVisibleAbsorptance() const override;

    double visibleReflectance() const;

    Quantity getSolarTransmittance(bool returnIP=false) const;

    Quantity getSolarReflectance(bool returnIP=false) const;

    double visibleTransmittance() const;

    virtual boost::optional<double> getVisibleTransmittance() const override;

    Quantity getVisibleTransmittance(bool returnIP) const;

    Quantity getVisibleReflectance(bool returnIP=false) const;

    double thermalHemisphericalEmissivity() const;

    Quantity getThermalHemisphericalEmissivity(bool returnIP=false) const;

    Quantity getThermalTransmittance(bool returnIP=false) const;

    Quantity getThickness(bool returnIP=false) const;

    double conductivity() const;

    Quantity getConductivity(bool returnIP=false) const;

    double shadetoGlassDistance() const;

    Quantity getShadetoGlassDistance(bool returnIP=false) const;

    bool isShadetoGlassDistanceDefaulted() const;

    double topOpeningMultiplier() const;

    Quantity getTopOpeningMultiplier(bool returnIP=false) const;

    bool isTopOpeningMultiplierDefaulted() const;

    double bottomOpeningMultiplier() const;

    Quantity getBottomOpeningMultiplier(bool returnIP=false) const;

    bool isBottomOpeningMultiplierDefaulted() const;

    double leftSideOpeningMultiplier() const;

    Quantity getLeftSideOpeningMultiplier(bool returnIP=false) const;

    bool isLeftSideOpeningMultiplierDefaulted() const;

    double rightSideOpeningMultiplier() const;

    Quantity getRightSideOpeningMultiplier(bool returnIP=false) const;

    bool isRightSideOpeningMultiplierDefaulted() const;

    double airflowPermeability() const;

    Quantity getAirflowPermeability(bool returnIP=false) const;

    bool isAirflowPermeabilityDefaulted() const;

    //@}
    /** @name Setters */
    //@{

    /** Set thickness to value (m). */
    virtual bool setThickness(double value) override;

    /** Sets the conductivity of the material in W/m*K, if possible. */
    bool setThermalConductivity(double value);

    /** Sets the conductance of the material in W/m^2*K, if possible. */
    bool setThermalConductance(double value);

    /** Sets the resistivity of the material in m*K/W, if possible. */
    bool setThermalResistivity(double value);

    /** Sets the resistance of the material in m^2*K/W, if possible. */
    bool setThermalResistance(double value);

    bool setThermalTransmittance(double value);

    bool setSolarTransmittance(double value);

    bool setSolarReflectance(double value);

    bool setVisibleTransmittance(double value);

    bool setVisibleReflectance(double value);

    bool setSolarTransmittance(const Quantity& solarTransmittance);

    bool setSolarReflectance(const Quantity& solarReflectance);

    bool setVisibleTransmittance(const Quantity& visibleTransmittance);

    bool setVisibleReflectance(const Quantity& visibleReflectance);

    bool setThermalHemisphericalEmissivity(double thermalHemisphericalEmissivity);

    bool setThermalHemisphericalEmissivity(const Quantity& thermalHemisphericalEmissivity);

    bool setThermalTransmittance(const Quantity& thermalTransmittance);

    bool setThickness(const Quantity& thickness);

    bool setConductivity(double conductivity);

    bool setConductivity(const Quantity& conductivity);

    bool setShadetoGlassDistance(double shadetoGlassDistance);

    bool setShadetoGlassDistance(const Quantity& shadetoGlassDistance);

    void resetShadetoGlassDistance();

    bool setTopOpeningMultiplier(double topOpeningMultiplier);

    bool setTopOpeningMultiplier(const Quantity& topOpeningMultiplier);

    void resetTopOpeningMultiplier();

    bool setBottomOpeningMultiplier(double bottomOpeningMultiplier);

    bool setBottomOpeningMultiplier(const Quantity& bottomOpeningMultiplier);

    void resetBottomOpeningMultiplier();

    bool setLeftSideOpeningMultiplier(double leftSideOpeningMultiplier);

    bool setLeftSideOpeningMultiplier(const Quantity& leftSideOpeningMultiplier);

    void resetLeftSideOpeningMultiplier();

    bool setRightSideOpeningMultiplier(double rightSideOpeningMultiplier);

    bool setRightSideOpeningMultiplier(const Quantity& rightSideOpeningMultiplier);

    void resetRightSideOpeningMultiplier();

    bool setAirflowPermeability(double airflowPermeability);

    bool setAirflowPermeability(const Quantity& airflowPermeability);

    void resetAirflowPermeability();

    //@}
    /** @name Other */
    //@{

    //@}
   protected:
   private:
    REGISTER_LOGGER("openstudio.model.Shade");

    openstudio::Quantity solarTransmittance_SI() const;
    openstudio::Quantity solarTransmittance_IP() const;
    openstudio::Quantity solarReflectance_SI() const;
    openstudio::Quantity solarReflectance_IP() const;
    openstudio::Quantity visibleTransmittance_SI() const;
    openstudio::Quantity visibleTransmittance_IP() const;
    openstudio::Quantity visibleReflectance_SI() const;
    openstudio::Quantity visibleReflectance_IP() const;
    openstudio::Quantity thermalHemisphericalEmissivity_SI() const;
    openstudio::Quantity thermalHemisphericalEmissivity_IP() const;
    openstudio::Quantity thermalTransmittance_SI() const;
    openstudio::Quantity thermalTransmittance_IP() const;
    openstudio::Quantity thickness_SI() const;
    openstudio::Quantity thickness_IP() const;
    openstudio::Quantity conductivity_SI() const;
    openstudio::Quantity conductivity_IP() const;
    openstudio::Quantity shadetoGlassDistance_SI() const;
    openstudio::Quantity shadetoGlassDistance_IP() const;
    openstudio::Quantity topOpeningMultiplier_SI() const;
    openstudio::Quantity topOpeningMultiplier_IP() const;
    openstudio::Quantity bottomOpeningMultiplier_SI() const;
    openstudio::Quantity bottomOpeningMultiplier_IP() const;
    openstudio::Quantity leftSideOpeningMultiplier_SI() const;
    openstudio::Quantity leftSideOpeningMultiplier_IP() const;
    openstudio::Quantity rightSideOpeningMultiplier_SI() const;
    openstudio::Quantity rightSideOpeningMultiplier_IP() const;
    openstudio::Quantity airflowPermeability_SI() const;
    openstudio::Quantity airflowPermeability_IP() const;
  };

} // detail

} // model
} // openstudio

#endif // MODEL_SHADE_IMPL_HPP

