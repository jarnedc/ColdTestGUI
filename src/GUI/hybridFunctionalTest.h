#include <cstring>
#include "../HWDescription/Cbc.h"
#include "../HWDescription/Module.h"
#include "../HWDescription/BeBoard.h"
#include "../HWInterface/CbcInterface.h"
#include "../HWInterface/BeBoardInterface.h"
#include "../HWDescription/Definition.h"
#include "../tools/HybridFunctionalTesting.h"
#include "../tools/OldCalibration.h"
#include "../Utils/argvparser.h"
#include "TROOT.h"
#include "TApplication.h"
#include "../Utils/Timer.h"

#include <TGClient.h>
#include <TGButton.h>
#include <TGFrame.h>
#include <TGLayout.h>
#include <TGWindow.h>
#include <TGLabel.h>
#include <TString.h>
#include <TGButtonGroup.h>
#include <iostream>
#include <fstream>
#include <stdio.h>  
#include <time.h>
#include <string> 
#include <sstream>
#include <TSystem.h>

using namespace Ph2_HwDescription;
using namespace Ph2_HwInterface;
using namespace Ph2_System;

using namespace CommandLineProcessing;

class IDList {
private:
   Int_t nID;   // creates unique widget's IDs
public:
   IDList() : nID(0) {}
   ~IDList() {}
   Int_t GetUnID(void) { return ++nID; }
};
class hybridFunctionalTest : public TGMainFrame {
private:
   //TGText              *StatusDisplay; //Displays the status of the calibration
   TGTextButton        *fExit;         // Exit text button
   TGTextButton        *fCalibration;  //Calibration text button
   TGTextButton        *fRedoCalibration;      //Text button to redo the calibration for the current hybrid
   //TGTextEntry         *fConfigXML;    //Configuration XML
   TGVButtonGroup      *fButtonGroup;  // Button group
   TGRadioButton       *fRadiob[2];    // Radio buttons
   IDList               IDs;           // Widget IDs generator
   TGLabel             *state;        // Label showing the state of the test
   TGLabel             *SerialNumberLabel; //Label showing the serial number of the hybrid that was scanned
   TGLabel             *serialNumber; //label showing the SerialNumber of the hybrid. This number is read from a file serial_number.txt
   TGGroupFrame        *fGframe;
   TGGroupFrame        *fGframe2;
public:
   hybridFunctionalTest(const TGWindow *p, UInt_t w, UInt_t h);
   virtual ~hybridFunctionalTest();
   void DoExit(void);
   void Calibrate(void);
   void WriteInfo(std::string);
   std::string ReadSerialNumberFromFile();
   int hybridTypeFromButton();
   void WriteResultsTestToDB(int);
   void SetGroupEnabled(Bool_t);
   int runTest(int);
   std::string * ReadDBLastLine();
   //void HandleReturn();
   bool run_calibration(int);
   const char * serialNumber_char;
   //std::string configXML = "settings/Calibration_8CBC.xml";
};
