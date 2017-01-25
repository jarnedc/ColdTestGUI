#include <TApplication.h>
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

const char * dataBasePath = "/root/Ph2_ACF_v1.40/Ph2_ACF/src/GUI/database.txt";
const char * serialNumberPath = "/root/Ph2_ACF_v1.40/Ph2_ACF/src/GUI/serial_number.txt";
const char * logPath = "/root/Ph2_ACF_v1.40/Ph2_ACF/src/GUI/log.txt";

class IDList {
private:
   Int_t nID;   // creates unique widget's IDs
  
public:
   IDList() : nID(0) {}
   ~IDList() {}
   Int_t GetUnID(void) { return ++nID; }
};
class MyButtonTest : public TGMainFrame {
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
   MyButtonTest(const TGWindow *p, UInt_t w, UInt_t h);
   virtual ~MyButtonTest();
   void DoExit(void);
   void Calibrate(void);
   void WriteInfo(std::string);
   std::string ReadSerialNumberFromFile();
   void WriteResultsTestToDB(int);
   void SetGroupEnabled(Bool_t);
   std::string * ReadDBLastLine();
   //void HandleReturn();
   bool run_calibration(int);
   const char * serialNumber_char;
   //std::string configXML = "settings/Calibration_8CBC.xml";
   ClassDef(MyButtonTest, 0)
   ofstream logbook;
};
