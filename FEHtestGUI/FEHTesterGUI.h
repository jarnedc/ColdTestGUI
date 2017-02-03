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
#include <TTimer.h>
#include "TThread.h"
#include "TF1.h"
#include "TColor.h"
#ifndef __CINT__
#include <thread>
#include <atomic>
#include <uhal/uhal.hpp> 
#include <uhal/log/exception.hpp>
#include <uhal/ProtocolControlHub.hpp>
#include "dbHandler.h"
#include "../ColdBoxDriver/Main_Driver/ColdBox.h"
#endif 
//const char * dataBasePath = "FEHtestGUI/database.txt";
//const char * serialNumberPath = "FEHtestGUI/serial_number.txt";
const char * logPath = "FEHtestGUI/GUIlog.txt";

//arrays containing the headers for the hybrids that are allowed in the serial code. For the productionHybridTypes and prototype8CBCHybridTypes a test with 8CBC configuration will be executed. For the prototype2CBCHybridTypes a test with two CBC configuration will be executed.
const std::string productionHybridTypes[10] = {"2SFE18L","2SFE18R","2SFE40L","2SFE40R","PSFE16L","PSFE16R","PSFE26L","PSFE26R","PSFE40L","PSFE40R"}; 
const std::string prototype2CBCHybridTypes[2] = {"2SFETWO","PSMOCKU"};
const std::string prototype8CBCHybridTypes[0];

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

class FEHTesterGUI : public TGMainFrame {
   RQ_OBJECT("FEHTesterGUI")
private:
   TGMainFrame         	*fMain;
   IDList              	 IDs;           // Widget IDs generator

   /*for the buttons*/
   TGVerticalFrame 	*fForButtons; 
   //TGRadioButton     	*fRadiob[2];    // Radio buttons
   //TGVButtonGroup   	*fButtonGroup;  // Button group
   TGTextButton        	*fExit;      
   //TGTextButton 	*fDraw;
   TGTextButton        	*fStartTest; 
   TGTextButton        	*fRetest;     
   
   /*Labels*/
   TGLabel             	*state;  
   TGLabel             	*SerialNumberLabel; 
   TGLabel		*EnvMonitoringLabel;
   TGLabel		*TestSummaryLabel; 
   TGLabel 		*DBStatusLabel;	
   TGGroupFrame        	*fGframe;
   TGGroupFrame        	*fGframe2;
   TGGroupFrame        	*fGframe3;
   TGGroupFrame        	*fGframe4;
   TGTextEntry 		*fTextEntry;

   /*for the canvases
   TRootEmbeddedCanvas 	*fEcanvas;
   TRootEmbeddedCanvas 	*fEcanvas1;
   TRootEmbeddedCanvas 	*fEcanvas2;
   TRootEmbeddedCanvas 	*fEcanvas3;
   TGHorizontalFrame 	*HorFramePlots;
   TGVerticalFrame 	*VerFramePlots1;
   TGVerticalFrame 	*VerFramePlots2;
   */

   TTimer		*timer;
   TThread 		*testerThread;
   /* for the popup screen
   TGLabel		*AlreadyTestedPopUpLabel;
   TGMainFrame		*fPopUp;
   TGVerticalFrame	*fPopupTopVertical;
   TGTextButton		*fProceed;
   TGTextButton 	*fCancelTest;
   TGHorizontalFrame	*fHorFrameForPopUpButtons;*/
#ifndef __CINT__
   dbHandler db;
   ColdBox cold_box;
#endif

public:
   
   FEHTesterGUI(const TGWindow *p, UInt_t w, UInt_t h);
   virtual ~FEHTesterGUI();
   void TranslateReturnValue(int);
   void DisactivateTestButton();
   void ActivateTestButton();
   void ActivateTestButtonAndState();
   void DoExit(void);
   void integratedtester();
   void WriteInfo(std::string);
   void UpdateEnvMonitoring();
   void launchThread();
   bool serNrAccordingToTemplate();
  


   /*old
   void DoDraw();
   std::string * ReadDBLastLine();
   void HandleReturn();
   void ClosePopUp();
   void integratedtesterAfterRetestSelected();
   void ClosePopUpAndProceedWithTest();
   void WriteResultsTestToDB(int,std::string,int);
   int runIntegratedTester(int, int);
   std::string configXML = "settings/Calibration_8CBC.xml";
   */
   
   /*Global*/
   TColor *red = new TColor(1000, 1, 0, 0);
   TColor *green = new TColor(1001, 0, 0.8, 0.2);
   TColor *blue = new TColor(1002, 0, 0, 1);
   int returnDateAndTime();
   std::string ReadCompleteFile(std::string);
   const char * serialNumber_char;
   ofstream logbook;
   int envCounter;
   int nrCBCs;
   int DateAndTime;
   bool debugFlag = true;
   std::string SerialNumberScanned;
   
   ClassDef(FEHTesterGUI, 0)
};

