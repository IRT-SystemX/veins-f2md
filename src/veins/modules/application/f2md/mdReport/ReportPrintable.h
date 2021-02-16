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

#ifndef __VEINS_ReportPrintable_H_
#define __VEINS_ReportPrintable_H_

#include <omnetpp.h>
#include <veins/modules/application/f2md/mdMessages/BasicSafetyMessage_m.h>
#include <veins/modules/application/f2md/mdReport/MDReport.h>
#include "../mdSupport/XmlWriter.h"
#include "../mdSupport/JsonWriter.h"

using namespace omnetpp;
using namespace veins;

class ReportPrintable {

private:

public:


    std::string getCheckXml(BsmCheck Check);
    std::string getBsmXml(BasicSafetyMessage bsm);

    std::string getCheckJson(BsmCheck Check);
    std::string getCheckJsonList(BsmCheck Check);
    std::string getBsmJson(BasicSafetyMessage bsm);

};

#endif
