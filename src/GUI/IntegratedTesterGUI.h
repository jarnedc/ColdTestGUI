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
#include <TCanvas.h>
#include <TGClient.h>
#include <TH1F.h>
#include <TRandom.h>
#include <TGFrame.h>
#include <TRootEmbeddedCanvas.h>
#include <RQ_OBJECT.h>
#include <TFile.h>
#include <ctime>

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
class IntegratedTesterGui : public TGMainFrame {
   RQ_OBJECT("IntegratedTesterGui")
private:
   TGMainFrame         *fMain;
   TGVerticalFrame *fTopVertical;
   TRootEmbeddedCanvas *fEcanvas;
   TRootEmbeddedCanvas *fEcanvas1;
   TRootEmbeddedCanvas *fEcanvas2;
   TRootEmbeddedCanvas *fEcanvas3;
   TGHorizontalFrame *HorFramePlots;
   TGVerticalFrame *VerFramePlots1;
   TGVerticalFrame *VerFramePlots2;
   //TGText              *StatusDisplay; //Displays the status of the calibration
   TGVerticalFrame *fForButtons; 
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
   TGLabel 		*TestSummary;
   TGGroupFrame        *fGframe;
   TGGroupFrame        *fGframe2;
   TGGroupFrame        *fGframe3;
   TGLabel		*TestSummaryLabel;
public:
   IntegratedTesterGui(const TGWindow *p, UInt_t w, UInt_t h);
   virtual ~IntegratedTesterGui();
   void TranslateReturnValue(int);
   void DisactivateTestButton();
   void ActivateTestButton();
   void DoExit(void);
   void DoDraw(int);
   void integratedtester(void);
   void WriteInfo(std::string);
   int returnDateAndTime();
   std::string ReadCompleteFile(std::string);
   std::string ReadSerialNumberFromFile();
   void WriteResultsTestToDB(int);
   void SetGroupEnabled(Bool_t);
   std::string * ReadDBLastLine();
   //void HandleReturn();
   int runIntegratedTester(int, int);
   const char * serialNumber_char;
   //std::string configXML = "settings/Calibration_8CBC.xml";
   ClassDef(IntegratedTesterGui, 0)
   ofstream logbook;
};
