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

#ifndef __VEINS_PCPolicy_H_
#define __VEINS_PCPolicy_H_

#include <tuple>
#include <omnetpp.h>
#include <veins/modules/application/f2md/mdEnumTypes/PseudoChangeTypes.h>
#include <veins/modules/application/f2md/mdStats/MDStatistics.h>
#include <veins/modules/application/f2md/mdSupport/MDMLib.h>
#include "../mdBase/NodeTable.h"
#include "../mdBase/InterTest.h"
#include "../mdBase/BsmCheck.h"
#include "../mdBase/InterTest.h"

#include "../mdEnumTypes/MbTypes.h"

using namespace veins;
using namespace omnetpp;


class PCPolicy {
protected:
    GeneralLib genLib = GeneralLib();
    MDMLib mdmLib = MDMLib();

    veins::Coord* curPosition;
    LAddress::L2Type* myId;
    int* pseudoNum;
    unsigned long* myPseudonym;

    long realPseudoNum;
    unsigned long myPseudonymList[MAX_PSEUDO_LIST];

    mbTypes::Mbs mbType;
    MDStatistics* mdAuthority;

    F2MDParameters * params;

public:
    unsigned long getNextPseudonym();

public:
    PCPolicy();
    PCPolicy(veins::Coord curPos, F2MDParameters * params);
    void setCurPosition(veins::Coord* curPosition);
    void setMyId(LAddress::L2Type* myId);
    void setMyPseudonym(unsigned long* myPseudonym);
    void setPseudoNum(int* pseudoNum);

    void checkPseudonymChange(pseudoChangeTypes::PseudoChange);

    double messageToleranceBuffer = 0;
    void disposablePCP();

    double lastChangeTime = 0;
    void periodicalPCP();

    double cumulativeDistance = 0;
    veins::Coord lastPos = veins::Coord(0, 0, 0);
    void distanceBasedPCP();

    bool firstChange = true;
    bool randDistanceSet = false;
    double randDistance = 800;
    bool randTimeSet = false;
    double randTime = 120;
    double changeTimerStart = 0;
    void car2carPCP();


    void randomPCP();

    void setMbType(mbTypes::Mbs mbType);
    void setMdAuthority(MDStatistics* mdAuthority);

};

#endif
