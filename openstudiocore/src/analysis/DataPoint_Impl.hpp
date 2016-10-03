/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) 2008-2016, Alliance for Sustainable Energy, LLC. All rights reserved.
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

#ifndef ANALYSIS_DATAPOINT_IMPL_HPP
#define ANALYSIS_DATAPOINT_IMPL_HPP

#include "AnalysisAPI.hpp"
#include "AnalysisObject_Impl.hpp"

#include "DataPoint.hpp"
#include "Problem.hpp"

#include "../model/Model.hpp"

#include "../runmanager/lib/Job.hpp"

#include "../utilities/idf/Workspace.hpp"
#include "../utilities/sql/SqlFile.hpp"
#include "../utilities/data/Attribute.hpp"
#include "../utilities/data/Tag.hpp"

#include "../utilities/core/FileReference.hpp"

#include <QVariant>

namespace openstudio {

namespace runmanager {
  class Job;
}

namespace analysis {

namespace detail {

  /** DataPoint_Impl is a AnalysisObject_Impl that is the implementation class for DataPoint.*/
  class ANALYSIS_API DataPoint_Impl : public AnalysisObject_Impl {
   public:
    /** @name Constructors and Destructors */
    //@{

    /** Constructor from variableValues. Called by Algorithm, may also be called directly by a
     *  user. After construction isComplete() == false. */
    DataPoint_Impl(const Problem& problem,
                   const std::vector<QVariant>& variableValues);

    /** Constructor provided for deserialization; not for general use. */
    DataPoint_Impl(const UUID& uuid,
                   const UUID& versionUUID,
                   const std::string& name,
                   const std::string& displayName,
                   const std::string& description,
                   const Problem& problem,
                   bool complete,
                   bool failed,
                   bool selected,
                   DataPointRunType runType,
                   const std::vector<QVariant>& variableValues,
                   const std::vector<double>& responseValues,
                   const openstudio::path& directory,
                   const boost::optional<FileReference>& osmInputData,
                   const boost::optional<FileReference>& idfInputData,
                   const boost::optional<FileReference>& sqlOutputData,
                   const boost::optional<runmanager::Job>& topLevelJob,
                   const std::vector<openstudio::path>& dakotaParametersFiles,
                   const std::vector<Tag>& tags,
                   const std::vector<Attribute>& outputAttributes);

    /** Constructor provided for deserialization; not for general use. */
    DataPoint_Impl(const UUID& uuid,
                   const UUID& versionUUID,
                   const std::string& name,
                   const std::string& displayName,
                   const std::string& description,
                   const UUID& problemUUID,
                   const boost::optional<UUID>& analysisUUID,
                   bool complete,
                   bool failed,
                   bool selected,
                   DataPointRunType runType,
                   const std::vector<QVariant>& variableValues,
                   const std::vector<double>& responseValues,
                   const openstudio::path& directory,
                   const boost::optional<FileReference>& osmInputData,
                   const boost::optional<FileReference>& idfInputData,
                   const boost::optional<FileReference>& sqlOutputData,
                   const boost::optional<runmanager::Job>& topLevelJob,
                   const std::vector<openstudio::path>& dakotaParametersFiles,
                   const std::vector<Tag>& tags,
                   const std::vector<Attribute>& outputAttributes);

    DataPoint_Impl(const DataPoint_Impl& other);

    virtual ~DataPoint_Impl() {}

    virtual AnalysisObject clone() const override;

    //@}
    /** @name Getters and Queries */
    //@{

    /** Returns true if DataPoint has access to the Problem that created it. Should be true
     *  unless DataPoint was deserialized from JSON and has not yet been assimilated back
     *  into its parent Analysis. */
    bool hasProblem() const;

    /** Returns the Problem used to create/associated with this DataPoint. */
    Problem problem() const;

    /** Returns the UUID of the Problem that created this DataPoint. */
    UUID problemUUID() const;

    /** Returns the UUID of the Analysis that parents this DataPoint. */
    boost::optional<UUID> analysisUUID() const;

    /** Returns true if the DataPoint has been simulated. \deprecated */
    bool isComplete() const;

    /** Returns true if the DataPoint has been simulated. */
    bool complete() const;

    /** Returns true if the DataPoint was simulated, but the simulation failed, or output results
     *  could not be retrieved for some other reason. */
    bool failed() const;

    /** Returns true if the DataPoint is selected (to be simulated in the next batch). */
    bool selected() const;

    DataPointRunType runType() const;

    /** Returns the variableValues to be applied in simulating this DataPoint. (That is, inputData
     *  will be the result of applying variableValues to the Analysis seed file.) */
    std::vector<QVariant> variableValues() const;

    /** Returns the value of the response functions for this DataPoint. Only non-empty if isComplete()
     *  and not failed() (and problem().numResponses() > 0). */
    std::vector<double> responseValues() const;

    /** Run directory for this DataPoint. Set by analysisdriver::AnalysisDriver. */
    openstudio::path directory() const;

    /** Returns the final OSM file in the workflow, if the DataPoint isComplete() but not
     *  failed(), and said file was located by problem(). */
    boost::optional<FileReference> osmInputData() const;

    /** Returns the final IDF file in the workflow, if the DataPoint isComplete() but not
     *  failed(), and said file was located by problem(). */
    boost::optional<FileReference> idfInputData() const;

    /** Returns the EnergyPlus SqLite output file, if the DataPoint isComplete() but not failed(),
     *  and said file was located by problem(). */
    boost::optional<FileReference> sqlOutputData() const;

    /** Returns the openstudio::Attribute and openstudio::result::OSResult XML files created 
     *  associated with this DataPoint, if complete() and not failed(). Otherwise, the return value 
     *  is .empty(). */
    std::vector<FileReference> xmlOutputData() const;

    /** If osmInputData() exists, returns the corresponding model::Model. Also caches the Model
     *  for future use. */
    boost::optional<model::Model> model() const;

    /** If idfInputData() exists, returns the corresponding Workspace. Also caches the Workspace
     *  for future use. */
    boost::optional<Workspace> workspace() const;

    /** If sqlOutputData() exists, returns the corresponding SqlFile, which is also available through
     *  model()->sqlFile(), if model() exists. Also caches the SqlFile for future use. */
    boost::optional<SqlFile> sqlFile() const;

    /** If xmlOutputData() exists, returns the corresponding openstudio::Attributes. Caches the
     *  Attributes for future use. */
    std::vector<Attribute> outputAttributes() const;

    /** Returns the outputAttributes() element with attributeName, if it exists. */
    boost::optional<Attribute> getOutputAttribute(const std::string& attributeName) const;

    std::vector<Tag> tags() const;

    bool isTag(const std::string& tagName) const;

    /** Returns true if testVariableValues.size() <= variableValues().size(), and any non-null
     *  values match. Otherwise, returns false. */
    bool matches(const std::vector<QVariant>& testVariableValues) const;

    /** Returns the top level job associated with this data point. 
     *  \sa Problem::getJobsByWorkflowStep */
    boost::optional<runmanager::Job> topLevelJob() const;

    /** Returns vector of dakotaParameterFiles associated with this data point. */
    std::vector<openstudio::path> dakotaParametersFiles() const;

    //@}
    /** @name Setters */
    //@{

    void setSelected(bool selected);

    void setRunType(const DataPointRunType& runType);

    void setDirectory(const openstudio::path& directory);

    void setTopLevelJob(const runmanager::Job& topLevelJob);

    void setDakotaParametersFiles(const std::vector<openstudio::path>& dakotaParametersFiles);

    void addTag(const std::string& tagName);

    void deleteTag(const std::string& tagName);

    //@}
    /** @name Actions */
    //@{

    /** Update high level results from json. */
    bool updateFromJSON(const std::string& json, boost::optional<runmanager::RunManager>& runManager);

    virtual bool updateFromJSON(const AnalysisJSONLoadResult& loadResult, boost::optional<runmanager::RunManager>& runManager);

    /** Whoever downloaded the zip file should have setDirectory(), and had the file placed in
     *  directory() / toPath("dataPoint.zip"). */
    bool updateDetails(boost::optional<runmanager::RunManager>& runManager);

    /** Clear model, workspace, and sqlFile from cache. */
    void clearFileDataFromCache() const;

    /** Clear model, workspace, sqlFile, and outputAttributes from cache. */
    void clearAllDataFromCache() const;

    virtual void clearResults();

    //@}
    /** @name Serialization */
    //@{

    bool saveJSON(const openstudio::path& p,
                  bool overwrite=false) const;

    std::ostream& toJSON(std::ostream& os) const;

    std::string toJSON() const;

    //@}
    /** @name Protected in or Absent from Public Class */
    //@{

    void setOsmInputData(const FileReference& file);

    void setIdfInputData(const FileReference& file);

    void setSqlOutputData(const FileReference& file);

    void setXmlOutputData(const std::vector<FileReference>& files);

    void markComplete();

    void markFailed();

    void setResponseValues(const std::vector<double>& values);

    void setProblem(const Problem& problem);

    virtual QVariant toVariant() const override;

    /** Contents of toVariant finalized for direct serialization (adds jsonMetadata and
     *  data_point moniker. */
    QVariant toTopLevelVariant() const;

    static DataPoint factoryFromVariant(const QVariant& variant,
                                        const VersionString& version,
                                        const boost::optional<Problem>& problem);

    static DataPoint fromVariant(const QVariant& variant, const VersionString& version);

    //@}
   protected:
    // relationship state
    // most of the time, m_problem should exist and m_parent should point to an Analysis
    boost::optional<Problem> m_problem;     // Problem to which this DataPoint refers
    // immediately after deserialization from json, may just have problem and analysis uuids
    UUID m_problemUUID;
    mutable boost::optional<UUID> m_analysisUUID;

    // pure data
    bool m_complete;                        // false after construction
                                            // set to true by Problem update
    bool m_failed;                          // false after construction
                                            // set to true by Problem update if point is unusable
    bool m_selected;                        // true after construction
                                            // used by Analysis to determine which points to run
    DataPointRunType m_runType;
    std::vector<QVariant> m_variableValues; // variable values for this run
    std::vector<double> m_responseValues;   // response function values for this run
    openstudio::path m_directory;           // directory containing results
    boost::optional<FileReference> m_osmInputData;  // an osm file
    boost::optional<FileReference> m_idfInputData;  // an idf file
    boost::optional<FileReference> m_sqlOutputData; // a sql file
    boost::optional<runmanager::Job> m_topLevelJob;
    std::vector<openstudio::path> m_dakotaParametersFiles;
    std::vector<Tag> m_tags;                // meta-data for query and display

    // cache variables
    mutable std::vector<FileReference> m_xmlOutputData; // attribute and OSResult xml
    mutable std::vector<Attribute> m_outputAttributes; // serialized and deserialized
    mutable boost::optional<model::Model> m_model;
    mutable boost::optional<Workspace> m_workspace;
    mutable boost::optional<SqlFile> m_sqlFile;    
   private:
    REGISTER_LOGGER("openstudio.analysis.DataPoint");   
  };

} // detail

} // model
} // openstudio

#endif // ANALYSIS_DATAPOINT_IMPL_HPP
