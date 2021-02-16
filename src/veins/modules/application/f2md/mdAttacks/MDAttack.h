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

#ifndef __VEINS_MDAttack_H_
#define __VEINS_MDAttack_H_

#include <tuple>
#include <omnetpp.h>
#include <veins/modules/application/f2md/mdSupport/networkLinksLib/LinkControl.h>

#include "../mdBase/NodeTable.h"
#include "../mdPCPolicies/PCPolicy.h"

#include "../F2MDParameters.h"

using namespace veins;
using namespace omnetpp;

class MDAttack {
protected:
    GeneralLib genLib = GeneralLib();

    BasicSafetyMessage* myBsm;
    int* myBsmNum;

    NodeTable* detectedNodes;

    unsigned long* myPseudonym;

    veins::Coord* curPosition;
    veins::Coord* curPositionConfidence;
    veins::Coord* curSpeed;
    veins::Coord* curSpeedConfidence;
    veins::Coord* curHeading;
    veins::Coord* curHeadingConfidence;
    veins::Coord* curAccel;
    veins::Coord* curAccelConfidence;


    double* myWidth;
    double* myLength;

    simtime_t* beaconInterval;

    PCPolicy* pcPolicy;

    BasicSafetyMessage saveAttackBsm = BasicSafetyMessage();

    BasicSafetyMessage staleMessagesBsm[MAX_STALE_NUM];
    int staleMessagesNum = 0;

    double localStopProb = 0;

    BasicSafetyMessage StopBsm;
    bool StopInitiated;

    bool DoSInitiated;

    unsigned long SybilMyOldPseudo = 0;
    unsigned long SybilPseudonyms[MAX_SYBIL_NUM];
    int SybilVehSeq = 0;

    double saveHeading = 0;

    unsigned long targetNode = 0;

    double MaxRandomPosX;
    double MaxRandomPosY;

    double ConstPosX;
    double ConstPosY;

    double ConstPosOffsetX;
    double ConstPosOffsetY;

    double ConstSpeedX;
    double ConstSpeedY;

    double ConstSpeedOffsetX;
    double ConstSpeedOffsetY;


    int localReplaySeqNum = 0;
    int ReplaySeq = 0;

    int localDosMultipleFreq = 0;
    int localDosMultipleFreqSybil = 0;

    int localSybilVehNumber = 0;

    double localSybilDistanceX = 0;
    double localSybilDistanceY = 0;

    F2MDParameters *params;


public:

    MDAttack();

    void init(attackTypes::Attacks myAttackType, double MaxRandomPosX,double MaxRandomPosY,F2MDParameters *params);

    BasicSafetyMessage launchAttack(attackTypes::Attacks myAttackType, LinkControl* LinkC);

    void setBeaconInterval(simtime_t* beaconInterval);
    void setCurHeading(veins::Coord* curHeading);
    void setCurHeadingConfidence(veins::Coord* curHeadingConfidence);
    void setCurPosition(veins::Coord* curPosition);
    void setCurPositionConfidence(veins::Coord* curPositionConfidence);
    void setCurSpeed(veins::Coord* curSpeed);
    void setCurSpeedConfidence(veins::Coord* curSpeedConfidence);
    void setCurAccel(veins::Coord* curAccel);
    void setCurAccelConfidence(veins::Coord* curAccelConfidence);

    void setDetectedNodes(NodeTable* detectedNodes);
    void setMyBsm(BasicSafetyMessage* myBsm);
    void setMyBsmNum(int* myBsmNum);
    void setMyLength(double* myLength);
    void setMyPseudonym(unsigned long * myPseudonym);
    void setMyWidth(double* myWidth);
    void setPcPolicy(PCPolicy* pcPolicy);

    unsigned long getTargetNode();
};

#endif
