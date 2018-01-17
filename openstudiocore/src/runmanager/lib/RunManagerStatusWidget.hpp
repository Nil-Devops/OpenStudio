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

#ifndef RUNMANAGER_LIB_RUNMANAGERSTATUSWIDGET_HPP
#define RUNMANAGER_LIB_RUNMANAGERSTATUSWIDGET_HPP

#include <string>
#include <QTimer>
#include "RunManager.hpp"
#include <runmanager/lib/ui_RunManagerStatusWidget.h>
#include "JobErrors.hpp"
#include "RunManagerAPI.hpp"
#include <QStandardItem>

namespace openstudio {
  namespace runmanager {

    //! QDialog based user interface for displaying RunManager queue job status to the user
    //! \sa http://doc.qt.nokia.com/qdialog.html
    class RUNMANAGER_API RunManagerStatusWidget : public QWidget
    {
      Q_OBJECT

      public:
        //! Creates a RunManagerStatusWidget dialog for displaying job status
        RunManagerStatusWidget(QWidget *parent = nullptr);
        virtual ~RunManagerStatusWidget();


        /// Sets the runmanager to monitor the status of
        void setRunManager(const RunManager &t_runmanager);

        /// Enables or disables the "goToOutput" menu option.
        void setGoToOutputEnabled(bool enabled);

        /// Returns a vector of QAction objects to display on a toolbar or some other easily accessible location
        std::vector<std::pair<bool, QAction *> > publicActions();

      signals:
        void jobSelectionCleared();
        void jobSelectionChanged(const openstudio::runmanager::Job &job);
        void goToOutput();


      private slots:
        void raiseJobPriority();
        void lowerJobPriority();
        void cancelResumeJob();
        void rerunJob();
        void showJobWarnings();
        void cleanupJobOutput();
        void deleteJob();
        void pausedToggled(bool t_paused);

        void rowInserted();
        void jobTreeSelectionChanged(const QItemSelection &t_selection);
        void completedJobTreeSelectionChanged(const QItemSelection &t_selection);

        void resizeCols();
        void openOutputFolder();
        void emitGoToOutput();
        void itemChanged(QStandardItem *i);
        void updateActions(const QModelIndexList &selection);
        void clearActions();
 
      private:
        REGISTER_LOGGER("openstudio::runmanager::RunManagerStatusWidget");
        //! Used for QDesigner classes.
        Ui::RunManagerStatusWidget ui;

        boost::optional<RunManager> m_runmanager;

        void openFile(const openstudio::path &p);

        QModelIndex getCurrentIndex();
        QModelIndexList getSelectedRows(); 

    };


} // runmanager namespace
} // openstudio namespace


#endif // RUNMANAGER_LIB_RUNMANAGERSTATUSWIDGET_HPP
