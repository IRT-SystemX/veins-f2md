/*******************************************************************************
* @author  Joseph Kamel 
* @email   josephekamel@gmail.com
* @date    28/11/2018
* @version 2.0
*
* SCA (Secure Cooperative Autonomous systems)
* Copyright (c) 2013, 2018 Institut de Recherche Technologique SystemX
* All rights reserved.
*******************************************************************************/

#ifndef __VEINS_BasicCheckReport_H_
#define __VEINS_BasicCheckReport_H_

#include <omnetpp.h>
#include <veins/modules/application/f2md/mdMessages/BasicSafetyMessage_m.h>
#include <veins/modules/application/f2md/mdReport/MDReport.h>
#include <veins/modules/application/f2md/mdReport/ReportPrintable.h>
#include "../mdSupport/XmlWriter.h"


using namespace omnetpp;

class BasicCheckReport: public MDReport {

    private:
        BsmCheck reportedCheck;

    public:
        BasicCheckReport(MDReport baseReport);
        void setReportedCheck(BsmCheck reportedCheck);
        std::string getReportPrintableXml();
        std::string getReportPrintableJson();

    };

#endif
