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

#include <veins/modules/application/f2md/mdReport/ReportPrintable.h>

std::string ReportPrintable::getCheckXml(BsmCheck Check){

    std::string tempStr = "";

    XmlWriter xml;
    xml.init();
    xml.writeOpenTag("BsmCheck");

     xml.writeStartElementTag("rP");
     xml.writeString(std::to_string(Check.getRangePlausibility()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("pP");
     xml.writeString(std::to_string(Check.getPositionPlausibility()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("sP");
     xml.writeString(std::to_string(Check.getSpeedPlausibility()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("pC");
     xml.writeString(std::to_string(Check.getPositionConsistancy()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("sC");
     xml.writeString(std::to_string(Check.getSpeedConsistancy()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("psC");
     xml.writeString(std::to_string(Check.getPositionSpeedConsistancy()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("psmC");
     xml.writeString(std::to_string(Check.getPositionSpeedMaxConsistancy()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("phC");
     xml.writeString(std::to_string(Check.getPositionHeadingConsistancy()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("sA");
     xml.writeString(std::to_string(Check.getSuddenAppearence()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("bF");
     xml.writeString(std::to_string(Check.getBeaconFrequency()));
     xml.writeEndElementTag();


     xml.writeStartElementTag("kPACS");
     xml.writeString(std::to_string(Check.getKalmanPACS()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("kPCS");
     xml.writeString(std::to_string(Check.getKalmanPCC()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("kPSCP");
     xml.writeString(std::to_string(Check.getKalmanPSCP()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("kPSCS");
     xml.writeString(std::to_string(Check.getKalmanPSCS()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("kPSCSP");
     xml.writeString(std::to_string(Check.getKalmanPSCSP()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("kPSCSS");
     xml.writeString(std::to_string(Check.getKalmanPSCSS()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("kSCC");
     xml.writeString(std::to_string(Check.getKalmanSCC()));
     xml.writeEndElementTag();


     tempStr = "n=\"";
     tempStr = tempStr + std::to_string(Check.getIntersection().getInterNum());
     tempStr = tempStr + "\"";

     xml.writeOpenTagWithAttribute("inT",tempStr);
     for (int var = 0; var < Check.getIntersection().getInterNum(); ++var) {
         tempStr = "id=\"";
         tempStr = tempStr + std::to_string(Check.getIntersection().getInterId(var));
         tempStr = tempStr + "\"";
         xml.writeStartElementTag("veh");
         xml.writeAttribute(tempStr);
         xml.writeString(std::to_string(Check.getIntersection().getInterValue(var)));
         xml.writeEndElementTag();
    }
     xml.writeCloseTag();
     xml.writeCloseTag();

     return xml.getOutString();

}

std::string ReportPrintable::getBsmXml(BasicSafetyMessage bsm){

    std::string tempStr = "";

    XmlWriter xml;
    xml.init();

    tempStr = "id=\"";
    tempStr = tempStr + std::to_string(bsm.getSenderPseudonym());
    tempStr = tempStr + "\"";

    tempStr = tempStr + "ct=\"";
    tempStr = tempStr + bsm.getCreationTime().str();
    tempStr = tempStr + "\"";

    tempStr = tempStr + "ts=\"";
    tempStr = tempStr + bsm.getArrivalTime().str();
    tempStr = tempStr + "\"";

    tempStr = tempStr + "mbt=\"";
    tempStr = tempStr + mbTypes::mbNames[bsm.getSenderMbType()];
    tempStr = tempStr + "\"";


    tempStr = tempStr + "att=\"";
    tempStr = tempStr + attackTypes::AttackNames[bsm.getSenderAttackType()];
    tempStr = tempStr + "\"";

    xml.writeOpenTagWithAttribute("Bsm", tempStr);

     xml.writeStartElementTag("Pos");
     tempStr = "(";
     tempStr = tempStr + std::to_string(bsm.getSenderPos().x);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderPos().y);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderPos().z);
     tempStr = tempStr + ")";
     xml.writeString(tempStr);
     xml.writeEndElementTag();

     xml.writeStartElementTag("PosConfidence");
     tempStr = "(";
     tempStr = tempStr + std::to_string(bsm.getSenderPosConfidence().x);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderPosConfidence().y);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderPosConfidence().z);
     tempStr = tempStr + ")";
     xml.writeString(tempStr);
     xml.writeEndElementTag();

     xml.writeStartElementTag("Speed");
     tempStr = "(";
     tempStr = tempStr + std::to_string(bsm.getSenderSpeed().x);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderSpeed().y);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderSpeed().z);
     tempStr = tempStr + ")";
     xml.writeString(tempStr);
     xml.writeEndElementTag();

     xml.writeStartElementTag("SpeedConfidence");
     tempStr = "(";
     tempStr = tempStr + std::to_string(bsm.getSenderSpeedConfidence().x);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderSpeedConfidence().y);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderSpeedConfidence().z);
     tempStr = tempStr + ")";
     xml.writeString(tempStr);
     xml.writeEndElementTag();

     xml.writeStartElementTag("Accel");
     tempStr = "(";
     tempStr = tempStr + std::to_string(bsm.getSenderAccel().x);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderAccel().y);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderAccel().z);
     tempStr = tempStr + ")";
     xml.writeString(tempStr);
     xml.writeEndElementTag();

     xml.writeStartElementTag("AccelConfidence");
     tempStr = "(";
     tempStr = tempStr + std::to_string(bsm.getSenderAccelConfidence().x);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderAccelConfidence().y);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderAccelConfidence().z);
     tempStr = tempStr + ")";
     xml.writeString(tempStr);
     xml.writeEndElementTag();

     xml.writeStartElementTag("Heading");
     tempStr = "(";
     tempStr = tempStr + std::to_string(bsm.getSenderHeading().x);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderHeading().y);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderHeading().z);
     tempStr = tempStr + ")";
     xml.writeString(tempStr);
     xml.writeEndElementTag();

     xml.writeStartElementTag("HeadingConfidence");
     tempStr = "(";
     tempStr = tempStr + std::to_string(bsm.getSenderHeadingConfidence().x);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderHeadingConfidence().y);
     tempStr = tempStr +",";
     tempStr = tempStr + std::to_string(bsm.getSenderHeadingConfidence().z);
     tempStr = tempStr + ")";
     xml.writeString(tempStr);
     xml.writeEndElementTag();

     xml.writeStartElementTag("Width");
     xml.writeString(std::to_string(bsm.getSenderWidth()));
     xml.writeEndElementTag();

     xml.writeStartElementTag("Length");
     xml.writeString(std::to_string(bsm.getSenderLength()));
     xml.writeEndElementTag();

//     xml.writeStartElementTag("MbType");
//     xml.writeString(bsm.getSenderMbTypeStr());
//     xml.writeEndElementTag();

     xml.writeCloseTag();

     return xml.getOutString();

}

std::string ReportPrintable::getCheckJson(BsmCheck Check){

    std::string tempStr = "";
    JsonWriter jw;

    jw.openJsonElement("BsmCheck",false);

    tempStr = jw.getSimpleTag("rP", std::to_string(Check.getRangePlausibility()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("pP", std::to_string(Check.getPositionPlausibility()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("sP", std::to_string(Check.getSpeedPlausibility()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("pC", std::to_string(Check.getPositionConsistancy()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("sC", std::to_string(Check.getSpeedConsistancy()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("psC", std::to_string(Check.getPositionSpeedConsistancy()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("psmC", std::to_string(Check.getPositionSpeedMaxConsistancy()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("phC", std::to_string(Check.getPositionHeadingConsistancy()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("sA", std::to_string(Check.getSuddenAppearence()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("bF", std::to_string(Check.getBeaconFrequency()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("kPACS", std::to_string(Check.getKalmanPACS()),true);
    jw.addTagToElement("BsmCheck", tempStr);
    tempStr = jw.getSimpleTag("kPCS", std::to_string(Check.getKalmanPCC()),true);
    jw.addTagToElement("BsmCheck", tempStr);
    tempStr = jw.getSimpleTag("kPSCP", std::to_string(Check.getKalmanPSCP()),true);
    jw.addTagToElement("BsmCheck", tempStr);
    tempStr = jw.getSimpleTag("kPSCS", std::to_string(Check.getKalmanPSCS()),true);
    jw.addTagToElement("BsmCheck", tempStr);
    tempStr = jw.getSimpleTag("kPSCSP", std::to_string(Check.getKalmanPSCSP()),true);
    jw.addTagToElement("BsmCheck", tempStr);
    tempStr = jw.getSimpleTag("kPSCSS", std::to_string(Check.getKalmanPSCSS()),true);
    jw.addTagToElement("BsmCheck", tempStr);
    tempStr = jw.getSimpleTag("kSCC", std::to_string(Check.getKalmanSCC()),true);
    jw.addTagToElement("BsmCheck", tempStr);

     jw.openJsonElementList("inT");

     JsonWriter jw2;
     jw2.openJsonElementList("inT");
     std::string inTStr = jw2.getJsonElementList("inT");

     for (int var = 0; var < Check.getIntersection().getInterNum(); ++var) {
         jw.openJsonElement("veh",true);
         tempStr = jw.getSimpleTag("pseudonym", std::to_string(Check.getIntersection().getInterId(var)),true);
         jw.addTagToElement("veh", tempStr);

         tempStr = jw.getSimpleTag("uVal", std::to_string(Check.getIntersection().getInterValue(var)),true);
         jw.addFinalTagToElement("veh", tempStr);

         tempStr = jw.getJsonElement("veh");

//         std::cout<<tempStr<<"\n";
//         std::size_t found = tempStr.find("{");
//         if (!(found!=std::string::npos)){
//             exit(0);
//         }

         if(var < Check.getIntersection().getInterNum() -1){
             jw.addTagToElement("inT", tempStr);
         }else{
             jw.addFinalTagToElement("inT", tempStr);
         }
    }

     inTStr = jw.getJsonElementList("inT");
     jw.addFinalTagToElement("BsmCheck", inTStr);
     return jw.getJsonElement("BsmCheck");

}

std::string ReportPrintable::getCheckJsonList(BsmCheck Check){

    std::string tempStr = "";
    JsonWriter jw;

    jw.openJsonElement("BsmCheck",true);

    tempStr = jw.getSimpleTag("rP", std::to_string(Check.getRangePlausibility()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("pP", std::to_string(Check.getPositionPlausibility()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("sP", std::to_string(Check.getSpeedPlausibility()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("pC", std::to_string(Check.getPositionConsistancy()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("sC", std::to_string(Check.getSpeedConsistancy()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("psC", std::to_string(Check.getPositionSpeedConsistancy()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("psmC", std::to_string(Check.getPositionSpeedMaxConsistancy()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("phC", std::to_string(Check.getPositionHeadingConsistancy()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("sA", std::to_string(Check.getSuddenAppearence()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("bF", std::to_string(Check.getBeaconFrequency()),true);
    jw.addTagToElement("BsmCheck", tempStr);

    tempStr = jw.getSimpleTag("kPACS", std::to_string(Check.getKalmanPACS()),true);
    jw.addTagToElement("BsmCheck", tempStr);
    tempStr = jw.getSimpleTag("kPCS", std::to_string(Check.getKalmanPCC()),true);
    jw.addTagToElement("BsmCheck", tempStr);
    tempStr = jw.getSimpleTag("kPSCP", std::to_string(Check.getKalmanPSCP()),true);
    jw.addTagToElement("BsmCheck", tempStr);
    tempStr = jw.getSimpleTag("kPSCS", std::to_string(Check.getKalmanPSCS()),true);
    jw.addTagToElement("BsmCheck", tempStr);
    tempStr = jw.getSimpleTag("kPSCSP", std::to_string(Check.getKalmanPSCSP()),true);
    jw.addTagToElement("BsmCheck", tempStr);
    tempStr = jw.getSimpleTag("kPSCSS", std::to_string(Check.getKalmanPSCSS()),true);
    jw.addTagToElement("BsmCheck", tempStr);
    tempStr = jw.getSimpleTag("kSCC", std::to_string(Check.getKalmanSCC()),true);
    jw.addTagToElement("BsmCheck", tempStr);


     jw.openJsonElementList("inT");

     JsonWriter jw2;
     jw2.openJsonElementList("inT");
     std::string inTStr = jw2.getJsonElementList("inT");

     for (int var = 0; var < Check.getIntersection().getInterNum(); ++var) {
         jw.openJsonElement("veh",true);
         tempStr = jw.getSimpleTag("pseudonym", std::to_string(Check.getIntersection().getInterId(var)),true);
         jw.addTagToElement("veh", tempStr);

         tempStr = jw.getSimpleTag("uVal", std::to_string(Check.getIntersection().getInterValue(var)),true);
         jw.addFinalTagToElement("veh", tempStr);

         tempStr = jw.getJsonElement("veh");

//         std::cout<<tempStr<<"\n";
//         std::size_t found = tempStr.find("{");
//         if (!(found!=std::string::npos)){
//             exit(0);
//         }

         if(var < Check.getIntersection().getInterNum() -1){
             jw.addTagToElement("inT", tempStr);
         }else{
             jw.addFinalTagToElement("inT", tempStr);
         }
    }

     inTStr = jw.getJsonElementList("inT");
     jw.addFinalTagToElement("BsmCheck", inTStr);
     return jw.getJsonElement("BsmCheck");

}


std::string ReportPrintable::getBsmJson(BasicSafetyMessage bsm){

    std::string tempStr = "";
    JsonWriter jw;
    jw.openJsonElement("Bsm",true);

    tempStr = jw.getSimpleTag("Pseudonym", std::to_string(bsm.getSenderPseudonym()),true);
    jw.addTagToElement("Bsm", tempStr);

    tempStr = jw.getSimpleTag("RealId", std::to_string(bsm.getSenderRealId()) ,true);
    jw.addTagToElement("Bsm", tempStr);

    tempStr = jw.getSimpleTag("CreationTime", bsm.getCreationTime().str(),true);
    jw.addTagToElement("Bsm", tempStr);

    tempStr = jw.getSimpleTag("ArrivalTime", bsm.getArrivalTime().str(),true);
    jw.addTagToElement("Bsm", tempStr);

    tempStr = jw.getSimpleTag("MbType", mbTypes::mbNames[bsm.getSenderMbType()],false);
    jw.addTagToElement("Bsm", tempStr);

    tempStr = jw.getSimpleTag("AttackType", attackTypes::AttackNames[bsm.getSenderAttackType()],false);
    jw.addTagToElement("Bsm", tempStr);

    jw.openJsonElementList("GpsCoord");
    jw.addTagToElement("GpsCoord", std::to_string(bsm.getSenderGpsCoordinates().x));
    jw.addTagToElement("GpsCoord", std::to_string(bsm.getSenderGpsCoordinates().y));
    jw.addFinalTagToElement("GpsCoord", std::to_string(bsm.getSenderGpsCoordinates().z));
    tempStr = jw.getJsonElementList("GpsCoord");
    jw.addTagToElement("Bsm", tempStr);

    jw.openJsonElementList("Pos");
    jw.addTagToElement("Pos", std::to_string(bsm.getSenderPos().x));
    jw.addTagToElement("Pos", std::to_string(bsm.getSenderPos().y));
    jw.addFinalTagToElement("Pos", std::to_string(bsm.getSenderPos().z));
    tempStr = jw.getJsonElementList("Pos");
    jw.addTagToElement("Bsm", tempStr);

    jw.openJsonElementList("PosConfidence");
    jw.addTagToElement("PosConfidence", std::to_string(bsm.getSenderPosConfidence().x));
    jw.addTagToElement("PosConfidence", std::to_string(bsm.getSenderPosConfidence().y));
    jw.addFinalTagToElement("PosConfidence", std::to_string(bsm.getSenderPosConfidence().z));
    tempStr = jw.getJsonElementList("PosConfidence");
    jw.addTagToElement("Bsm", tempStr);

    jw.openJsonElementList("Speed");
    jw.addTagToElement("Speed", std::to_string(bsm.getSenderSpeed().x));
    jw.addTagToElement("Speed", std::to_string(bsm.getSenderSpeed().y));
    jw.addFinalTagToElement("Speed", std::to_string(bsm.getSenderSpeed().z));
    tempStr = jw.getJsonElementList("Speed");
    jw.addTagToElement("Bsm", tempStr);

    jw.openJsonElementList("SpeedConfidence");
    jw.addTagToElement("SpeedConfidence", std::to_string(bsm.getSenderSpeedConfidence().x));
    jw.addTagToElement("SpeedConfidence", std::to_string(bsm.getSenderSpeedConfidence().y));
    jw.addFinalTagToElement("SpeedConfidence", std::to_string(bsm.getSenderSpeedConfidence().z));
    tempStr = jw.getJsonElementList("SpeedConfidence");
    jw.addTagToElement("Bsm", tempStr);

    jw.openJsonElementList("Accel");
    jw.addTagToElement("Accel", std::to_string(bsm.getSenderAccel().x));
    jw.addTagToElement("Accel", std::to_string(bsm.getSenderAccel().y));
    jw.addFinalTagToElement("Accel", std::to_string(bsm.getSenderAccel().z));
    tempStr = jw.getJsonElementList("Accel");
    jw.addTagToElement("Bsm", tempStr);

    jw.openJsonElementList("AccelConfidence");
    jw.addTagToElement("AccelConfidence", std::to_string(bsm.getSenderAccelConfidence().x));
    jw.addTagToElement("AccelConfidence", std::to_string(bsm.getSenderAccelConfidence().y));
    jw.addFinalTagToElement("AccelConfidence", std::to_string(bsm.getSenderAccelConfidence().z));
    tempStr = jw.getJsonElementList("AccelConfidence");
    jw.addTagToElement("Bsm", tempStr);

    jw.openJsonElementList("Heading");
    jw.addTagToElement("Heading", std::to_string(bsm.getSenderHeading().x));
    jw.addTagToElement("Heading", std::to_string(bsm.getSenderHeading().y));
    jw.addFinalTagToElement("Heading", std::to_string(bsm.getSenderHeading().z));
    tempStr = jw.getJsonElementList("Heading");
    jw.addTagToElement("Bsm", tempStr);

    jw.openJsonElementList("HeadingConfidence");
    jw.addTagToElement("HeadingConfidence", std::to_string(bsm.getSenderHeadingConfidence().x));
    jw.addTagToElement("HeadingConfidence", std::to_string(bsm.getSenderHeadingConfidence().y));
    jw.addFinalTagToElement("HeadingConfidence", std::to_string(bsm.getSenderHeadingConfidence().z));
    tempStr = jw.getJsonElementList("HeadingConfidence");
    jw.addTagToElement("Bsm", tempStr);

    tempStr = jw.getSimpleTag("Width",std::to_string(bsm.getSenderWidth()),true);
    jw.addTagToElement("Bsm", tempStr);

    tempStr = jw.getSimpleTag("Length",std::to_string(bsm.getSenderLength()),true);
    jw.addFinalTagToElement("Bsm", tempStr);
    return jw.getJsonElement("Bsm");
}

