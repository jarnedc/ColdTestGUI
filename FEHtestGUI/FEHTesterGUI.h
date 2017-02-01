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
#include "TF1.h"
#ifndef __CINT__
#include <thread>
#include <atomic>
#include <uhal/uhal.hpp> 
#include <uhal/log/exception.hpp>
#include <uhal/ProtocolControlHub.hpp>
#include "dbHandler.h"
#include "../ColdBoxDriver/Main_Driver/ColdBox.h"
#endif 
const char * dataBasePath = "FEHtestGUI/database.txt";
const char * serialNumberPath = "FEHtestGUI/serial_number.txt";
const char * logPath = "FEHtestGUI/log.txt";

const std::string productionHybridTypes[10] = {"2SFE18L","2SFE18R","2SFE40L","2SFE40R","PSFE16L","PSFE16R","PSFE26L","PSFE26R","PSFE40L","PSFE40R"}; 
const std::string prototype2CBCHybridTypes[1] = {"2SFETWO"};
const std::string prototype8CBCHybridTypes[1] = {"PSMOCKU"};

void *runThreadFunc(void *);

class IDList {
private:
   Int_t nID;   // creates unique widget's IDs
  
public:
   IDList() : nID(0) {  
   }
   ~IDList() {}
   Int_t GetUnID(void) { return ++nID; }
};

class IntegratedTesterGui : public TGMainFrame {
   RQ_OBJECT("IntegratedTesterGui")
private:
   TGMainFrame         	*fMain;
   TRootEmbeddedCanvas 	*fEcanvas;
   TRootEmbeddedCanvas 	*fEcanvas1;
   TRootEmbeddedCanvas 	*fEcanvas2;
   TRootEmbeddedCanvas 	*fEcanvas3;
   TGHorizontalFrame 	*HorFramePlots;
   TGVerticalFrame 	*VerFramePlots1;
   TGVerticalFrame 	*VerFramePlots2;
   TGVerticalFrame 	*fForButtons; 
   TGRadioButton       	*fRadiob[2];    // Radio buttons
   TGTextButton        	*fExit;         // Exit text button
   TGTextButton 	*fDraw;
   TGTextButton        	*fStartTest;  //Calibration text button
   TGTextButton        	*fRetest;      //Text button to redo the calibration for the current hybrid
   TGVButtonGroup      	*fButtonGroup;  // Button group
   IDList              	 IDs;           // Widget IDs generator
   TGLabel             	*state;        // Label showing the state of the test
   TGLabel             	*SerialNumberLabel; //Label showing the serial number of the hybrid that was scanned
   TGLabel             	*serialNumber; //label showing the SerialNumber of the hybrid. This number is read from a file serial_number.txt
   TGLabel 		*TestSummary;
   TGLabel		*EnvMonitoringLabel;
   TGGroupFrame        	*fGframe;
   TGGroupFrame        	*fGframe2;
   TGGroupFrame        	*fGframe3;
   TGGroupFrame        	*fGframe4;
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
   ColdBox cold_box;
#endif

public:
   
   IntegratedTesterGui(const TGWindow *p, UInt_t w, UInt_t h);
   virtual ~IntegratedTesterGui();
   bool hybridAlreadyTested();
   void TranslateReturnValue(int);
   void DisactivateTestButton();
   void ActivateTestButton();
   void ActivateTestButtonAndState();
   void DoExit(void);
   void DoDraw();
   void integratedtester();
   void WriteInfo(std::string);
   int returnDateAndTime();
   std::string ReadCompleteFile(std::string);
   void WriteResultsTestToDB(int,std::string,int);
   const char * serialNumber_char;
   ofstream logbook;
   void UpdateEnvMonitoring();
   void launchThread();
   bool serNrAccordingToTemplate();
   int envCounter;
   int nrCBCs;
   int DateAndTime;
   std::string SerialNumberScanned;
   //std::string * ReadDBLastLine();
   //void HandleReturn();
   //int runIntegratedTester(int, int);
   //std::string configXML = "settings/Calibration_8CBC.xml";
   //void ClosePopUp();
   //void integratedtesterAfterRetestSelected();
   //void ClosePopUpAndProceedWithTest();
 
   ClassDef(IntegratedTesterGui, 0)
};

