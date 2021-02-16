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

#include <veins/modules/application/f2md/mdSupport/RelativeOffset.h>
#define STEP_G 0.1/3
#define STEP_PI 0.01

RelativeOffset::RelativeOffset(veins::Coord *curPosConfidence,
        veins::Coord *curSpeedConfidence, veins::Coord* curHeadingConfidence,veins::Coord* curAccelConfidence,
        double* deltaRPosition, double* deltaThetaPosition, double* deltaSpeed,
        double* deltaHeading,double* deltaAccel) {
    this->curPosConfidence = curPosConfidence;
    this->curSpeedConfidence = curSpeedConfidence;
    this->curHeadingConfidence = curHeadingConfidence;
    this->curAccelConfidence = curAccelConfidence;
    this->deltaRPosition = deltaRPosition;
    this->deltaThetaPosition = deltaThetaPosition;
    this->deltaSpeed = deltaSpeed;
    this->deltaHeading = deltaHeading;
    this->deltaAccel = deltaAccel;
}

double RelativeOffset::getGaussianRand(double mean, double stddev) {

    struct timespec tm;
    clock_gettime(CLOCK_REALTIME, &tm);

    random::mt19937 rng(tm.tv_nsec);

    std::normal_distribution<> d { mean, stddev };
    return d(rng);
}

veins::Coord RelativeOffset::OffsetPosition(veins::Coord curPosition) {
    MDMLib mdmLib = MDMLib();
    GeneralLib genLib = GeneralLib();
    double stepr = fabs(getGaussianRand(0, STEP_G * curPosConfidence->x));

    double gsim = 0.5;
    if (*deltaRPosition > curPosConfidence->x / 2) {
        gsim = mdmLib.gaussianSum(*deltaRPosition, curPosConfidence->x);
    }
    double upDownProb = genLib.RandomDouble(0, 1);

    if (upDownProb < gsim) {
        if (*deltaRPosition > stepr) {
            *deltaRPosition = *deltaRPosition - stepr;
        } else {
            *deltaRPosition = *deltaRPosition + stepr;
        }
    } else {
        *deltaRPosition = *deltaRPosition + stepr;
        if (*deltaRPosition > curPosConfidence->x) {
            *deltaRPosition = *deltaRPosition - stepr;
        }
    }

    double stepTheta = genLib.RandomDouble(-(STEP_PI / 2.0) * PI,
            (STEP_PI / 2.0) * PI);
    *deltaThetaPosition = *deltaThetaPosition + stepTheta;

    double stepX = *deltaRPosition * cos(*deltaThetaPosition);
    double stepY = *deltaRPosition * sin(*deltaThetaPosition);

    //non gaussian
    //r = genLib.RandomDouble(-curPosConfidence, curPosConfidence);

    return veins::Coord(curPosition.x + stepX, curPosition.y + stepY, 0);
}

veins::Coord RelativeOffset::OffsetSpeed(veins::Coord curSpeed) {
    MDMLib mdmLib = MDMLib();
    GeneralLib genLib = GeneralLib();
    double stepS = fabs(getGaussianRand(0, STEP_G * curSpeedConfidence->x));
    double gsim = 0.5;
    if (*deltaSpeed > curSpeedConfidence->x / 2) {
        gsim = mdmLib.gaussianSum(*deltaSpeed, curSpeedConfidence->x);
    }

    double upDownProb = genLib.RandomDouble(0, 1);
    if (upDownProb < gsim) {
        if (*deltaSpeed > stepS) {
            *deltaSpeed = *deltaSpeed - stepS;
        } else {
            *deltaSpeed = *deltaSpeed + stepS;
        }
    } else {
        *deltaSpeed = *deltaSpeed + stepS;
        if (*deltaSpeed > curSpeedConfidence->x) {
            *deltaSpeed = *deltaSpeed - stepS;
        }
    }
    return veins::Coord(curSpeed.x + *deltaSpeed, curSpeed.y + *deltaSpeed, 0);
}

veins::Coord RelativeOffset::OffsetAccel(veins::Coord curAccel) {
    MDMLib mdmLib = MDMLib();
    GeneralLib genLib = GeneralLib();
    double stepS = fabs(getGaussianRand(0, STEP_G * curAccelConfidence->x));
    double gsim = 0.5;
    if (*deltaAccel > curAccelConfidence->x / 2) {
        gsim = mdmLib.gaussianSum(*deltaAccel, curAccelConfidence->x);
    }

    double upDownProb = genLib.RandomDouble(0, 1);
    if (upDownProb < gsim) {
        if (*deltaAccel > stepS) {
            *deltaAccel = *deltaAccel - stepS;
        } else {
            *deltaAccel = *deltaAccel + stepS;
        }
    } else {
        *deltaAccel = *deltaAccel + stepS;
        if (*deltaAccel > curAccelConfidence->x) {
            *deltaAccel = *deltaAccel - stepS;
        }
    }
    return veins::Coord(curAccel.x + *deltaAccel, curAccel.y + *deltaAccel, 0);

}

veins::Coord RelativeOffset::OffsetHeading(veins::Coord curHeading) {
    MDMLib mdmLib = MDMLib();
    GeneralLib genLib = GeneralLib();
    double headingAngle = mdmLib.calculateHeadingAngle(curHeading);

    double stepH = fabs(
            getGaussianRand(0, STEP_G * curHeadingConfidence->x));

    double gsim = 0.5;
    if (*deltaHeading > curHeadingConfidence->x / 2) {
        gsim = mdmLib.gaussianSum(*deltaHeading, curHeadingConfidence->x);
    }

    double upDownProb = genLib.RandomDouble(0, 1);
    if (upDownProb < gsim) {
        *deltaHeading = *deltaHeading - stepH;
        if (*deltaHeading < curHeadingConfidence->x / 2) {
            *deltaHeading = *deltaHeading + stepH;
        }
    } else {
        *deltaHeading = *deltaHeading + stepH;
        if (*deltaHeading > curHeadingConfidence->x / 2) {
            *deltaHeading = *deltaHeading - stepH;
        }
    }

    headingAngle = headingAngle + *deltaHeading;
    double x = cos(headingAngle * PI / 180);
    double y = sin(headingAngle * PI / 180);

    return veins::Coord(x, -y, curHeading.z);

}

