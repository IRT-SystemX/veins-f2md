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

#include <stdio.h>
#include <stdlib.h>     /* atof */
#include <boost/algorithm/string.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <veins/modules/application/f2md/mdApplications/AggregationApp.h>
#include <iostream>
#include <string>
#include <vector>


using namespace std;
using namespace boost;

AggrigationApp::AggrigationApp(int version,double Threshold ,double devValue, double deltaTrustTime,
        int maxBsmTrustNum) :
        MDApplication(version) {
    this->Threshold = Threshold;
    this->devValue = devValue;
    this->deltaTrustTime = deltaTrustTime;
    this->maxBsmTrustNum = maxBsmTrustNum;
}

bool AggrigationApp::CheckNodeForReport(unsigned long myPseudonym,
        BasicSafetyMessage * bsm, BsmCheck * bsmCheck, NodeTable * detectedNodes) {

    bool checkFailed = false;

    double tempFactor = 0;
    prntApp->incAll(mbTypes::intMbs[bsm->getSenderMbType()]);
    prntAppInst->incAll(mbTypes::intMbs[bsm->getSenderMbType()]);
    calculateMinFactor(bsmCheck);
    incrementDetailedFlags(bsm,bsmCheck,Threshold);


    unsigned long senderId = bsm->getSenderPseudonym();

    MDMHistory * mdmHist = detectedNodes->getMDMHistoryAddr(senderId);
    NodeHistory * nodeHist = detectedNodes->getNodeHistoryAddr(senderId);

    BsmCheck bsmCheckList[maxBsmTrustNum];
    int bsmCheckListSize = 0;

    for (int var = 0; var < nodeHist->getBSMNum(); ++var) {
        if (bsmCheckListSize < maxBsmTrustNum) {
            if (mdmLib.calculateDeltaTime(bsm, nodeHist->getBSMAddr(var))
                    < deltaTrustTime) {
                bsmCheckList[bsmCheckListSize] = mdmHist->getBsmCheck(var,
                        version);
                bsmCheckListSize++;
            }
        }
    }

    double factorList[bsmCheckListSize];

    //std::cout<< "RangePlausibility" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getRangePlausibility();
    }
    tempFactor = AggregateFactorsListDouble(bsmCheck->getRangePlausibility(),
            factorList, bsmCheckListSize);

    if (tempFactor < Threshold) {
        checkFailed = true;
    }
    //std::cout<< "PositionConsistancy" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getPositionConsistancy();
    }
    tempFactor = AggregateFactorsListDouble(bsmCheck->getPositionConsistancy(),
            factorList, bsmCheckListSize);

    if (tempFactor < Threshold) {
        checkFailed = true;
    }

    //std::cout<< "PositionSpeedConsistancy" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getPositionSpeedConsistancy();
    }
    tempFactor = AggregateFactorsListDouble(
            bsmCheck->getPositionSpeedConsistancy(), factorList,
            bsmCheckListSize);

    if (tempFactor < Threshold) {
        checkFailed = true;
    }

    //std::cout<< "PositionSpeedMaxConsistancy" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getPositionSpeedMaxConsistancy();
    }
    tempFactor = AggregateFactorsListDouble(
            bsmCheck->getPositionSpeedMaxConsistancy(), factorList,
            bsmCheckListSize);
    if (tempFactor < Threshold) {
        checkFailed = true;
    }

    //std::cout<< "SpeedConsistancy" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getSpeedConsistancy();
    }
    tempFactor = AggregateFactorsListDouble(bsmCheck->getSpeedConsistancy(),
            factorList, bsmCheckListSize);
    if (tempFactor < Threshold) {
        checkFailed = true;
    }

    //std::cout<< "SpeedPlausibility" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getSpeedPlausibility();
    }
    tempFactor = AggregateFactorsListDouble(bsmCheck->getSpeedPlausibility(),
            factorList, bsmCheckListSize);
    if (tempFactor < Threshold) {
        checkFailed = true;
    }

    //std::cout<< "PositionPlausibility" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getPositionPlausibility();
    }
    tempFactor = AggregateFactorsListDouble(bsmCheck->getPositionPlausibility(),
            factorList, bsmCheckListSize);
    if (tempFactor < Threshold) {
        checkFailed = true;
    }

    //std::cout<< "BeaconFrequency" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getBeaconFrequency();
    }
    tempFactor = AggregateFactorsListDouble(bsmCheck->getBeaconFrequency(),
            factorList, bsmCheckListSize);
    if (tempFactor < Threshold) {
        checkFailed = true;
    }


    //std::cout<< "PositionHeadingConsistancy" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getPositionHeadingConsistancy();
    }
    tempFactor = AggregateFactorsListDouble(
            bsmCheck->getPositionHeadingConsistancy(), factorList,
            bsmCheckListSize);
    if (tempFactor < Threshold) {
        checkFailed = true;
    }

    //std::cout<< "kalmanPSCP" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getKalmanPSCP();
    }
    tempFactor = AggregateFactorsListDouble(bsmCheck->getKalmanPSCP(),
            factorList, bsmCheckListSize);
    if (tempFactor < Threshold) {
        checkFailed = true;
    }

    //std::cout<< "kalmanPSCS" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getKalmanPSCS();
    }
    tempFactor = AggregateFactorsListDouble(bsmCheck->getKalmanPSCS(),
            factorList, bsmCheckListSize);
    if (tempFactor < Threshold) {
        checkFailed = true;
    }

    //std::cout<< "kalmanPSCSP" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getKalmanPSCSP();
    }
    tempFactor = AggregateFactorsListDouble(bsmCheck->getKalmanPSCSP(),
            factorList, bsmCheckListSize);
    if (tempFactor < Threshold) {
        checkFailed = true;
    }

    //std::cout<< "kalmanPSCSS" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getKalmanPSCSS();
    }
    tempFactor = AggregateFactorsListDouble(bsmCheck->getKalmanPSCSS(),
            factorList, bsmCheckListSize);
    if (tempFactor < Threshold) {
        checkFailed = true;
    }

    //std::cout<< "kalmanPCS" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getKalmanPCC();
    }
    tempFactor = AggregateFactorsListDouble(bsmCheck->getKalmanPCC(),
            factorList, bsmCheckListSize);

    if (tempFactor < Threshold) {
        checkFailed = true;
    }

    //std::cout<< "kalmanPACS" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getKalmanPACS();
    }
    tempFactor = AggregateFactorsListDouble(bsmCheck->getKalmanPACS(),
            factorList, bsmCheckListSize);

    if (tempFactor < Threshold) {
        checkFailed = true;
    }

    //std::cout<< "kalmanSCC" << '\n';
    for (int var = 0; var < bsmCheckListSize; ++var) {
        factorList[var] = bsmCheckList[var].getKalmanSCC();
    }
    tempFactor = AggregateFactorsListDouble(bsmCheck->getKalmanSCC(),
            factorList, bsmCheckListSize);
    if (tempFactor < Threshold) {
        checkFailed = true;
    }

    InterTest inter = bsmCheck->getIntersection();
    for (int var = 0; var < inter.getInterNum(); ++var) {
        double curInferFactor = inter.getInterValue(var);

        for (int i = 0; i < bsmCheckListSize; ++i) {
            double IdIndex = bsmCheckList[i].getIntersection().getIdIndex(
                    inter.getInterId(var));
            if (IdIndex != -1) {
                factorList[i] = bsmCheckList[i].getIntersection().getInterValue(
                        IdIndex);
            } else {
                factorList[i] = 1;
            }
        }
        //std::cout<< "Intersection" << '\n';
        tempFactor = AggregateFactorsListDouble(curInferFactor, factorList,
                bsmCheckListSize);
        if (tempFactor < Threshold) {
            checkFailed = true;
        }
    }

    if (checkFailed) {
        prntApp->incCumulFlags(mbTypes::intMbs[bsm->getSenderMbType()]);
        prntAppInst->incCumulFlags(mbTypes::intMbs[bsm->getSenderMbType()]);
        bsmCheck->setReported(true);
    }
    return checkFailed;
}

//double AggrigationApp::AggregateFactorsListDouble(double curFactor,
//        double *factorList, int factorListSize) {
//    double averageFactor = curFactor;
//    double divValue = 1;
//    for (int var = 0; var < factorListSize; ++var) {
//        double decValue =  pow(devValue, var+1);
//        averageFactor = averageFactor + factorList[var]*decValue;
//        divValue = divValue + decValue;
//    }
//    averageFactor = averageFactor / divValue;
//    return averageFactor;
//}

double AggrigationApp::getMinFactor() {
    return minFactor;
}

double AggrigationApp::AggregateFactorsListDouble(double curFactor, double *factorList,
        int factorListSize) {

    if (version == 1) {
        double averageFactor = curFactor;
        for (int var = 0; var < factorListSize; ++var) {
            averageFactor = averageFactor + factorList[var];
        }
        averageFactor = averageFactor / (factorListSize + 1);

        return averageFactor;
    } else {
        if (curFactor <= 0) {
            return 0;
        } else {
            double averageFactor = curFactor;
            for (int var = 0; var < factorListSize; ++var) {
                averageFactor = averageFactor + factorList[var];
            }
            averageFactor = averageFactor / (factorListSize + 1);
            return averageFactor;
        }
    }
}

//
//double AggrigationApp::AggregateFactorsListDouble(double curFactor, double *factorList,
//        int factorListSize) {
//
//    if (version == 1) {
//        double averageFactor = curFactor;
//        for (int var = 0; var < factorListSize; ++var) {
//            averageFactor = averageFactor + factorList[var];
//        }
//        averageFactor = averageFactor / (factorListSize + 1);
//
//        return averageFactor;
//    } else {
//        if (curFactor <= 0) {
//            return 0;
//        } else {
//            double averageFactor = curFactor;
//            for (int var = 0; var < factorListSize; ++var) {
//                averageFactor = averageFactor + factorList[var];
//            }
//            averageFactor = averageFactor / (factorListSize + 1);
//            return averageFactor;
//        }
//    }
//}

//best rate / faulty
//bool AggrigationApp::AggregateFactorsList(double curFactor, double *factorList,
//        int factorListSize) {
//    if (version == 1) {
//        double averageFactor = curFactor;
//        for (int var = 0; var < factorListSize; ++var) {
//            averageFactor = averageFactor + factorList[var];
//        }
//        averageFactor = averageFactor / (factorListSize + 1);
//        if ((averageFactor) <= 0.5) {
//            return true;
//        } else {
//            return false;
//        }
//    } else {
//        if (curFactor <= 0) {
//            return true;
//        } else {
//            double averageFactor = curFactor;
//            for (int var = 0; var < factorListSize; ++var) {
//                averageFactor = averageFactor + factorList[var];
//            }
//            averageFactor = averageFactor / (factorListSize + 1);
//
//            if ((averageFactor) <= 0.5) {
//                return true;
//            } else {
//                return false;
//            }
//        }
//    }
//}

