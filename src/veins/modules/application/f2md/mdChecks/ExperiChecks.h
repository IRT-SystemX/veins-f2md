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

#ifndef __VEINS_ExperiChecks_H_
#define __VEINS_ExperiChecks_H_

#include <tuple>

#include <omnetpp.h>
#include <veins/modules/application/f2md/mdBase/NodeMDMHistory.h>
#include <veins/modules/application/f2md/mdBase/NodeTable.h>
#include <veins/modules/application/f2md/mdReport/MDReport.h>
#include <veins/modules/application/f2md/mdStats/MDStatistics.h>
#include <veins/modules/application/f2md/mdSupport/networkLinksLib/LinkControl.h>
#include "../mdBase/NodeTable.h"
#include "../mdBase/InterTest.h"
#include "../mdBase/BsmCheck.h"
#include "../mdBase/InterTest.h"
#include "../mdSupport/MDMLib.h"
#include "veins/modules/obstacle/ObstacleControl.h"
#include "veins/modules/obstacle/Obstacle.h"

#include "../mdSupport/kalmanLib/Kalman_SVI.h"
#include "../mdSupport/kalmanLib/Kalman_SI.h"


using namespace veins;
using namespace omnetpp;

class ExperiChecks {
private:
    int version = 0;
    unsigned long myPseudonym;
    veins::Coord myPosition;
    veins::Coord myPositionConfidence;

    veins::Coord myHeading;
    veins::Coord myHeadingConfidence;

    veins::Coord mySize;

    MDMLib mdmLib;

    LinkControl* LinkC;

    double MAX_PLAUSIBLE_SPEED = 0;
    double MAX_PLAUSIBLE_ACCEL = 0;
    double MAX_PLAUSIBLE_DECEL = 0;
    F2MDParameters * params;

    double RangePlausibilityCheck(veins::Coord*, veins::Coord*, veins::Coord*, veins::Coord*);
    double PositionPlausibilityCheck(veins::Coord*, veins::Coord*, double, double);
    double SpeedPlausibilityCheck(double, double);
    double PositionConsistancyCheck(veins::Coord * curPosition,
            veins::Coord * curPositionConfidence, veins::Coord * oldPosition,
            veins::Coord * oldPositionConfidence, double time);
    double SpeedConsistancyCheck(double, double, double, double, double);
    double IntersectionCheck(veins::Coord * nodePosition1,
            veins::Coord * nodePositionConfidence1, veins::Coord * nodePosition2,
            veins::Coord* nodePositionConfidence2, veins::Coord * nodeHeading1,
            veins::Coord * nodeHeading2, veins::Coord* nodeSize1, veins::Coord * nodeSize2,
            double deltaTime);
    InterTest MultipleIntersectionCheck(NodeTable * detectedNodes,
            BasicSafetyMessage * bsm);

    double PositionSpeedMaxConsistancyCheck(veins::Coord * curPosition,
            veins::Coord * curPositionConfidence, veins::Coord * oldPosition,
            veins::Coord * oldPositionConfidence, double curSpeed,
            double curSpeedConfidence, double oldspeed,
            double oldSpeedConfidence, double time);

    double PositionSpeedConsistancyCheck(veins::Coord * curPosition,
            veins::Coord * curPositionConfidence, veins::Coord * oldPosition,
            veins::Coord * oldPositionConfidence, double curSpeed,
            double curSpeedConfidence, double oldspeed,
            double oldSpeedConfidence, double time);

    void KalmanPositionSpeedConsistancyCheck(veins::Coord * curPosition,
            veins::Coord * curPositionConfidence, veins::Coord * curSpeed, veins::Coord * curAccel,
            veins::Coord * curSpeedConfidence, double time, Kalman_SVI * kalmanSVI,
            double retVal[]);

    void KalmanPositionSpeedScalarConsistancyCheck(veins::Coord * curPosition,veins::Coord * oldPosition,
            veins::Coord * curPositionConfidence, veins::Coord * curSpeed, veins::Coord * curAccel,
            veins::Coord * curSpeedConfidence, double time, Kalman_SC * kalmanSC,
            double retVal[]);

    double KalmanPositionConsistancyCheck(veins::Coord * curPosition, veins::Coord * oldPosition, veins::Coord * curPosConfidence,
             double time, Kalman_SI * kalmanSI);

    double KalmanPositionAccConsistancyCheck(veins::Coord * curPosition, veins::Coord * curSpeed, veins::Coord * curPosConfidence,
             double time, Kalman_SI * kalmanSI);

    double KalmanSpeedConsistancyCheck(veins::Coord * curSpeed, veins::Coord * curAccel, veins::Coord * curSpeedConfidence,
            double time, Kalman_SI * kalmanSI);

    double PositionHeadingConsistancyCheck(veins::Coord * curHeading,
            veins::Coord * curHeadingConfidence, veins::Coord * oldPosition,
            veins::Coord * oldPositionConfidence, veins::Coord * curPositionConfidence,
            veins::Coord * curPosition, double deltaTime, double curSpeed,
            double curSpeedConfidence);

    double BeaconFrequencyCheck(double, double);
    double SuddenAppearenceCheck(veins::Coord*, veins::Coord*, veins::Coord*, veins::Coord*);

    void PrintBsmCheck(unsigned long senderPseudonym, BsmCheck bsmCheck);

    void resetAll();

public:
    ExperiChecks(int version, unsigned long myPseudonym, veins::Coord myPosition,
            veins::Coord myPositionConfidence, veins::Coord myHeading,
            veins::Coord myHeadingConfidence, veins::Coord mySize, veins::Coord myLimits,
            LinkControl* LinkC,F2MDParameters * params);
    BsmCheck CheckBSM(BasicSafetyMessage * bsm, NodeTable * detectedNodes);

};

#endif
