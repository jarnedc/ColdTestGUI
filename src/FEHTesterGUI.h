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
#include "TGTextEntry.h"
#include "FEHTester.h"
#include <X11/Xlib.h>
#include <TTimer.h>
#include "TThread.h"
#ifndef __CINT__
#include <thread>
#include <atomic>
#include <uhal/uhal.hpp> 
#include <uhal/log/exception.hpp>
#include <uhal/ProtocolControlHub.hpp>
#include "../Utils/dbHandler.h"
#endif 
/* 
const char * dataBasePath = "/root/Ph2_ACF_v1.40/Ph2_ACF/src/database.txt";
const char * serialNumberPath = "/root/Ph2_ACF_v1.40/Ph2_ACF/src/serial_number.txt";
const char * logPath = "/root/Ph2_ACF_v1.40/Ph2_ACF/src/log.txt";
*/
const char * dataBasePath = "src/database.txt";
const char * serialNumberPath = "src/serial_number.txt";
const char * logPath = "src/log.txt";


void *runThreadFunc(void *);
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
  // TGHorizontalFrame 	*fTopTopHorizontal;
 //  TGVerticalFrame *fTopVertical;
 //  TGVerticalFrame *fTopVerticalRight;
   TRootEmbeddedCanvas *fEcanvas;
   TRootEmbeddedCanvas *fEcanvas1;
   TRootEmbeddedCanvas *fEcanvas2;
   TRootEmbeddedCanvas *fEcanvas3;
   TGHorizontalFrame *HorFramePlots;
   TGVerticalFrame *VerFramePlots1;
   TGVerticalFrame *VerFramePlots2;
   //TGText              *StatusDisplay; //Displays the status of the calibration
   TGVerticalFrame *fForButtons; 
   TGRadioButton       *fRadiob[2];    // Radio buttons
   TGTextButton        *fExit;         // Exit text button
   TGTextButton        *fCalibration;  //Calibration text button
   TGTextButton        *fRedoCalibration;      //Text button to redo the calibration for the current hybrid
   //TGTextEntry         *fConfigXML;    //Configuration XML
   TGVButtonGroup      *fButtonGroup;  // Button group
  IDList               IDs;           // Widget IDs generator
   TGLabel             *state;        // Label showing the state of the test
   TGLabel             *SerialNumberLabel; //Label showing the serial number of the hybrid that was scanned
   TGLabel             *serialNumber; //label showing the SerialNumber of the hybrid. This number is read from a file serial_number.txt
   TGLabel 		*TestSummary;
   TGLabel		*EnvMonitoringLabel;
   TGGroupFrame        *fGframe;
   TGGroupFrame        *fGframe2;
   TGGroupFrame        *fGframe3;
   TGGroupFrame        *fGframe4;
 //  TGGroupFrame 	*fGframe5;
   TGLabel		*TestSummaryLabel;
   TGTextEntry 		*fTextEntry;
   TGLabel 		*DBStatusLabel;	

   TTimer		*timer;
   TThread 		*testerThread;
   bool			testerDone;

   TGLabel		*AlreadyTestedPopUpLabel;
   TGMainFrame		*fPopUp;
   TGVerticalFrame	*fPopupTopVertical;
   TGTextButton		*fProceed;
   TGTextButton 	*fCancelTest;
   TGHorizontalFrame	*fHorFrameForPopUpButtons;
#ifndef __CINT__
   dbHandler db;
#endif

public:
 
   IntegratedTesterGui(const TGWindow *p, UInt_t w, UInt_t h);
   virtual ~IntegratedTesterGui();
   bool hybridAlreadyTested();
 //  void DoAlreadyTestedPopUp();
   void TranslateReturnValue(int);
   void DisactivateTestButton();
   void ActivateTestButton();
   void DoExit(void);
   void DoDraw(int);
   void integratedtester();
   void WriteInfo(std::string);
   int returnDateAndTime();
   std::string ReadCompleteFile(std::string);
   std::string ReadSerialNumberFromFile();
   void WriteResultsTestToDB(int,std::string,int);
   void SetGroupEnabled(Bool_t);
   //std::string * ReadDBLastLine();
   //void HandleReturn();
   //int runIntegratedTester(int, int);
   const char * serialNumber_char;
   //std::string configXML = "settings/Calibration_8CBC.xml";
   ofstream logbook;
   void UpdateEnvMonitoring();
  // void ClosePopUp();
   void launchThread();
   void UpdateSerNumberLabel();	
//   void integratedtesterAfterRetestSelected();
//   void ClosePopUpAndProceedWithTest();
   int envCounter;
   ClassDef(IntegratedTesterGui, 0)
};

