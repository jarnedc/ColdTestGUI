#include "FEHTesterGUI.h"
void *runThreadFunc(void * f){
	IntegratedTesterGui* myObject = (IntegratedTesterGui*)f;
	myObject->integratedtester();
  
	return 0;
}

IntegratedTesterGui::IntegratedTesterGui(const TGWindow *p, UInt_t w, UInt_t h)
{ 
//    db.isConnected();
   // Create a main frame
   fMain = new TGMainFrame(p,w,h);
   TGHorizontalFrame *fTopTopHorizontal = new TGHorizontalFrame(fMain,1600,1000);
   TGVerticalFrame *fTopVertical = new TGVerticalFrame(fTopTopHorizontal,800,1000);
   TGVerticalFrame *fTopVerticalRight = new TGVerticalFrame(fTopTopHorizontal,800,1000);


   //******************************************************************************
   //******************************left part of the GUI(for tester control)********
   //******************************************************************************
   //--=====================================CANVASES===========================--//
   // Create canvas widget
   TGHorizontalFrame *HorFramePlots = new TGHorizontalFrame(fTopVertical,800,300);
   TGVerticalFrame *VerFramePlots1 = new TGVerticalFrame(HorFramePlots,300,300);
   fEcanvas = new TRootEmbeddedCanvas("Ecanvas",VerFramePlots1,300,150);
   fEcanvas1 = new TRootEmbeddedCanvas("Ecanvas1",VerFramePlots1,300,150);
   VerFramePlots1->AddFrame(fEcanvas,new TGLayoutHints(kLHintsTop,2,2,2,2));
   VerFramePlots1->AddFrame(fEcanvas1,new TGLayoutHints(kLHintsTop,2,2,2,2));

   TGVerticalFrame *VerFramePlots2 = new TGVerticalFrame(HorFramePlots,300,300);
   fEcanvas2 = new TRootEmbeddedCanvas("Ecanvas2",VerFramePlots2,300,150);
   fEcanvas3 = new TRootEmbeddedCanvas("Ecanvas3",VerFramePlots2,300,150);
   VerFramePlots2->AddFrame(fEcanvas2,new TGLayoutHints(kLHintsTop,2,2,2,2));
   VerFramePlots2->AddFrame(fEcanvas3,new TGLayoutHints(kLHintsTop,2,2,2,2));	
   
   HorFramePlots->AddFrame(VerFramePlots1,new TGLayoutHints(kLHintsLeft|kLHintsExpandY, 2,2,2,2));
   HorFramePlots->AddFrame(VerFramePlots2,new TGLayoutHints(kLHintsLeft|kLHintsExpandX, 2,2,2,2));

   fTopVertical->AddFrame(HorFramePlots, new TGLayoutHints(kLHintsExpandX|kLHintsTop,2,2,2,2));
                     
  
   //SetCleanup(kDeepCleanup);
   Connect("CloseWindow()", "IntegratedTesterGui", this, "DoExit()");
   //DontCallClose();
   //--====================================USER INPUT============================--//
   TGHorizontalFrame *fForUserInput = new TGHorizontalFrame(fTopVertical,800,300);

   //--RADIO BUTTONS--// 
   TGHorizontalFrame *fHL2 = new TGHorizontalFrame(fForUserInput,800,300);
   fButtonGroup = new TGVButtonGroup(fHL2, "Hybrid selection");
   fRadiob[0] = new TGRadioButton(fButtonGroup, new TGHotString("2CBC (this is the small one)"),IDs.GetUnID());
   fRadiob[0]->SetToolTipText("Select this if you want to run the callibration for the 2CBC hybrid. This is the PCB containing 2 CBC chips.");
   fRadiob[1] = new TGRadioButton(fButtonGroup, new TGHotString("8CBC (this is the big one)"),IDs.GetUnID());
   fRadiob[1]->SetToolTipText("Select this if you want to run the callibration for the 8CBC hybrid. This is the PCB containing 8 CBC chips. This is set as default.");
   fButtonGroup->Show();
   fHL2->AddFrame(fButtonGroup,new TGLayoutHints(kLHintsNoHints,2,2,2,2));
   fForUserInput->AddFrame(fHL2, new TGLayoutHints(kLHintsLeft|kLHintsExpandX,2,2,2,2));
 // fForUserInput->AddFrame(fHL2, new TGLayoutHints(kLHintsLeft|kLHintsExpandY,2,2,2,2));
  
   //--PUSH BUTTONS--//
   TGVerticalFrame *fForButtons = new TGVerticalFrame(fForUserInput);

   fStartTest = new TGTextButton(fForButtons, "&Start testing", IDs.GetUnID());
   fStartTest->Connect("Clicked()", "IntegratedTesterGui", this, "launchThread()");
   fStartTest->SetToolTipText("Click this button to start the calibration. Depending on which hybrid you selected in the list above (2CBC or 8CBC) it will automatically run with the correct settings");
   fForButtons->AddFrame(fStartTest, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX, 2,2,2,2));
 
  //define the Exit text button
   fExit = new TGTextButton(fForButtons, "&Exit this application", IDs.GetUnID());
   fExit->Connect("Clicked()", "IntegratedTesterGui", this, "DoExit()");
   fExit->SetToolTipText("Click this button if you want to exit this GUI"); 
   fForButtons->AddFrame(fExit, new TGLayoutHints(kLHintsCenterX|kLHintsExpandX,2,2,2,2));
   
   
   fForUserInput->AddFrame(fForButtons,new TGLayoutHints(kLHintsLeft|kLHintsExpandX,2,2,2,2));
//   fForUserInput->AddFrame(fForButtons,new TGLayoutHints(kLHintsLeft|kLHintsExpandY,2,2,2,2));
 
   fTopVertical->AddFrame(fForUserInput,new TGLayoutHints(kLHintsExpandX|kLHintsTop,1,1,1,1)); 
 
   //--========================LABELS=================================--//
   TGVerticalFrame *fForLabels = new TGVerticalFrame(fTopVertical);
   //define the status label
   fGframe = new TGGroupFrame(fForLabels,"Status of the test"); 
   state = new TGLabel(fGframe, "I am waiting for your input");
   fGframe->AddFrame(state, new TGLayoutHints(kLHintsExpandY));
   fForLabels->AddFrame(fGframe,new TGLayoutHints(kLHintsTop|kLHintsExpandX,2,2,2,2)); 
  //fGframe->SetMaxWidth(100); 
   //define the serialNumber label
   fGframe2 = new TGGroupFrame(fForLabels, "Serial Number");
   SerialNumberLabel = new TGLabel(fGframe2, "The serial number comes here");
   fGframe2->AddFrame(SerialNumberLabel,new TGLayoutHints(kLHintsExpandY));
   fForLabels->AddFrame(fGframe2,new TGLayoutHints(kLHintsTop|kLHintsExpandX,2,2,2,2));

   fGframe3 = new TGGroupFrame(fForLabels, "Test Summary");
   TestSummaryLabel = new TGLabel(fGframe3, "\n \n \n The test summary comes here \n \n \n");
   fGframe3->AddFrame(TestSummaryLabel,new TGLayoutHints(kLHintsExpandY));
   fForLabels->AddFrame(fGframe3,new TGLayoutHints(kLHintsTop|kLHintsExpandX,2,2,2,2));

   fGframe4 = new TGGroupFrame(fForLabels, "DB Status");
   DBStatusLabel = new TGLabel(fGframe4, "The DB status comes here");
   fGframe4->AddFrame(DBStatusLabel,new TGLayoutHints(kLHintsExpandY));
   fForLabels->AddFrame(fGframe4,new TGLayoutHints(kLHintsTop|kLHintsExpandX,2,2,2,2));

/*
   TestSummaryLabel = new TGLabel(fTopVertical, "\n \n \n The test summary comes here \n \n \n");
   TestSummaryLabel->SetTitle("Test Summary");
   fTopVertical->AddFrame(TestSummaryLabel, new TGLayoutHints(kLHintsExpandY, 2, 2, 2, 2));
 */

   //--======================TEXT EDIT==============================--//
   //define the textedit for the serial number
   fTextEntry = new TGTextEntry(fForLabels, new TGTextBuffer(100));
   fForLabels->AddFrame(fTextEntry, new TGLayoutHints(kLHintsExpandX|kLHintsTop, 5, 5, 5, 5));
   fTextEntry->Connect("ReturnPressed()", "IntegratedTesterGui", this, "UpdateSerNumberLabel()");    	
   fTopVertical->AddFrame(fForLabels,new TGLayoutHints(kLHintsBottom|kLHintsExpandX,1,1,1,1));

   fTopTopHorizontal->AddFrame(fTopVertical,new TGLayoutHints(kLHintsLeft|kLHintsExpandX, 2,2,2,2));	
   //******************************************************************************
   //******************************right part of the GUI(for environmental control)
   //******************************************************************************
  
   TGGroupFrame *fGframe5 = new TGGroupFrame(fTopVerticalRight, "test label for env monitoring");
   EnvMonitoringLabel = new TGLabel(fGframe5, "test test");
   fGframe5->AddFrame(EnvMonitoringLabel,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY));
   fTopVerticalRight->AddFrame(fGframe5,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,2,2,2,2));  

   fTopTopHorizontal -> AddFrame(fTopVerticalRight,new TGLayoutHints(kLHintsLeft|kLHintsExpandX|kLHintsExpandY, 2,2,2,2));
   
   envCounter = 0;

   //--================BACK TO THE MAIN========================================-// 	
   fMain->AddFrame(fTopTopHorizontal,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY));
   //Default state
   fButtonGroup->SetState(kTRUE);
   fMain->SetWindowName("2CBC/8CBC Hybrid calibration");
   fMain->MapSubwindows();
//   fMain->Resize(1600,1000);
   fMain->Resize(GetDefaultSize());
   fMain->MapWindow();
   fButtonGroup->SetRadioButtonExclusive(kTRUE);
   fRadiob[1]->SetOn();


   testerThread = nullptr;
   TTimer *timer = new TTimer();
   timer->Connect("Timeout()", "IntegratedTesterGui", this, "UpdateEnvMonitoring()");
   timer->Start(1000, kFALSE);
};

void IntegratedTesterGui::UpdateEnvMonitoring(){
     if(testerThread != nullptr){
     	if(testerThread->GetState()==6){ //6 means thread has finished
      		std::cout << "State:  " << testerThread->GetState() << std::endl;
     		testerThread->Join();
		//std::cout << "We can activate button and join" << std::endl;
		//ActivateTestButton();
		delete testerThread;
                testerThread = nullptr;
 	}
     }	
    else{std::cout<<"not done yet" << std::endl;}	
    envCounter++;  
    EnvMonitoringLabel->SetText((std::to_string(envCounter)).c_str());
}

void IntegratedTesterGui::UpdateSerNumberLabel(){
        std::string SerialNumberScanned = fTextEntry->GetText(); 
   	SerialNumberLabel->SetText(SerialNumberScanned.c_str());
	std::cout << "the text in the text edit has changed" << std::endl;   
}

void IntegratedTesterGui::DoDraw(int dateAndTime) {
   char ROOTfile[200];
   snprintf(ROOTfile , 200, "Results/IntegratedTesterFromGUI-%d/Summary.root", (int)dateAndTime);
   
    TFile *f = new TFile(ROOTfile);   
    f->ls();
    TH1F *h_Offsets_Fe0Cbc1 = (TH1F*)f->Get("h_Offsets_Fe0Cbc1");
    h_Offsets_Fe0Cbc1->Draw();
    TCanvas *fCanvas = fEcanvas->GetCanvas();
    fCanvas->cd();
    fCanvas->Update();

    TH1F *h_Occupancy_Fe0Cbc0 = (TH1F*)f->Get("h_Occupancy_Fe0Cbc0");
    h_Occupancy_Fe0Cbc0->Draw();
    TCanvas *fCanvas1 = fEcanvas1->GetCanvas();
    fCanvas1->cd();
    fCanvas1->Update();


    TH1F *fHistShortsTop = (TH1F*)f->Get("fHistShortsTop");
    fHistShortsTop->Draw();
    TCanvas *fCanvas2 = fEcanvas2->GetCanvas();
    fCanvas2->cd();
    fCanvas2->Update();


    TH1F *fHistShortsBottom = (TH1F*)f->Get("fHistShortsBottom");
    fHistShortsBottom->Draw();
    TCanvas *fCanvas3 = fEcanvas3->GetCanvas();
    fCanvas3->cd();
    fCanvas3->Update();

}

IntegratedTesterGui::~IntegratedTesterGui()
{
   // Destructor.
   Cleanup();
}
void IntegratedTesterGui::launchThread(){
  WriteInfo("-->Start Integrated Tester was Clicked");
  DisactivateTestButton(); 
  TestSummaryLabel->SetText("Test status should come here after test.");
  DBStatusLabel->SetText("DB info");
  state->SetText("TEST RUNNING");
  gSystem->ProcessEvents();
  std::cout << "Before creating the thread" << std::endl;
  testerThread = new TThread("testerThread", runThreadFunc, (void *) this );
  std::cout << "After the thread was created" << std::endl;		
  testerThread->Run();
  std::cout << "after running the thread" << std::endl;	
}


void IntegratedTesterGui::integratedtester()

{
  int DateAndTime = returnDateAndTime();
  time_t t = time(0); 
  std::string SerialNumberScanned = fTextEntry->GetText(); 
     
   //get the serial number from the text field 
   SerialNumberLabel->SetText(SerialNumberScanned.c_str());

  //get the nr of CBCs from the radio buttons
  int nrCBCs = 0;  
  if(fRadiob[0]->IsOn()){nrCBCs = 2;}
  else if(fRadiob[1]->IsOn()){nrCBCs = 8;}
  //TODO:add seprate tries and catches	
  int returnValue = 1;
   try{
	try{//try running the integratedtester	
		std::cout << "before running the integratedtester routine" << std::endl;  
 		returnValue = integratedtesterForGUI(nrCBCs, DateAndTime); 
		std::cout << "after running the integratedtester routine" << std::endl;
 		std::cout << "the returnValue in the try: " << returnValue << std::endl;
  		TranslateReturnValue(returnValue);
	}
 	 catch(uhal::exception::ControlHubTargetTimeout &e){
		std::cout << "Timeout from the GLIB. Is the GLIB powered? Try to ping the GLIB..." <<std::endl;
        	state->SetText("FAILED, the GLIB did not respond. Try to PING IT!!! Is it powered/connected?");
		gSystem->ProcessEvents(); 
  	}  
/* 	should include the correct header 	
    	catch(Ph2_HwInterface::Exception &e){
		std::cout << "Ph2_HwInterface::Exception thrown. Try to power cycle the GLIB..." <<std::endl;
        	state->SetText("FAILED, the GLIB did not respond. Try to PING IT!!! Is it powered/connected?");
       	 	gSystem->ProcessEvents();
   	}*/
        catch(...){std::cout << "Something went wrong during the running of the test!" << std::endl;} //catch all others errors that can occur durint the running of the integratedtester    
	
	try{//try writing to the DB
		//db.insertNewTestResult(SerialNumberScanned, std::to_string(returnValue), std::to_string(returnValue==0 ? 1: 0), std::to_string(nrCBCs),std::to_string(t));
		WriteResultsTestToDB(DateAndTime,SerialNumberScanned,returnValue); 
 		DBStatusLabel->SetText("Values Written To DB");
	}
	catch(...){
		std::cout << "Something went wrong during writing to DB!" << std::endl;
	}

	try{//try drawing the histo's on the GUI
        	DoDraw(DateAndTime);
	}
	catch(...){
		std::cout << "Something went wrong during plotting of the plots on the GUI!" << std::endl;
	}

	try{//try showing TestReport.txt in the GUI
        	char Summaryfile[200];
		snprintf(Summaryfile , 200, "Results/IntegratedTesterFromGUI-%d/TestReport.txt", DateAndTime);
		TestSummaryLabel->SetText(ReadCompleteFile(std::string(Summaryfile)).c_str());
        	TestSummaryLabel->Layout();
	}
	catch(...){
		std::cout << "Something went wrong showing the TestReport.txt in the GUI" << std::endl;
	}
        WriteInfo("End of test was reached!");
 }
  
  catch(...){
       std::cout << "SOMETHING SOMETHING ... went wrong" <<std::endl;
	state->SetText("FAILED, an error was caught. Solution not (yet) specified!");
        gSystem->ProcessEvents();
   }
   std::cout << "the status of the test when returned to gui: " << returnValue << std::endl;
   ActivateTestButton();
}

bool IntegratedTesterGui::hybridAlreadyTested(){
   //should use IntegratedTesterGui::ReadSerialNumberFromFile and the a search database option
   return true;
}

void IntegratedTesterGui::TranslateReturnValue(int outcomeOfIntegratedTester){
	std::cout << "outcomeOfIntegratedTester in GUI: " << outcomeOfIntegratedTester << std::endl; 
	switch(outcomeOfIntegratedTester){
	case 0:
		state->SetText("TEST SUCCESFULL");
        	gSystem->ProcessEvents();
		break;
 	case 1:
		state->SetText(("FAILED, return code: " + std::to_string(outcomeOfIntegratedTester)).c_str());
		gSystem->ProcessEvents();
		break;
	case 101:
		state->SetText(("FAILED, hybrid failed current consumption test (return code: " + std::to_string(outcomeOfIntegratedTester) + ")").c_str());
	        gSystem->ProcessEvents();
		break;
	case 102:
		state->SetText(("FAILED, hybrid failed register test (return code: " + std::to_string(outcomeOfIntegratedTester) + ")").c_str());
	        gSystem->ProcessEvents();
		break;
	case 103:
		state->SetText(("FAILED, hybrid failed short finding test (return code: " + std::to_string(outcomeOfIntegratedTester) + ")").c_str());
        	gSystem->ProcessEvents();
		break;
	default:
		state->SetText("FAILED");
        	gSystem->ProcessEvents();		 
	}
}

void IntegratedTesterGui::DisactivateTestButton(){
   fStartTest->SetState(kButtonDisabled);
   fButtonGroup->SetState(kFALSE);
   //fExit->SetState(kButtonDisabled);
}
void IntegratedTesterGui::ActivateTestButton(){
   fStartTest->SetEnabled();
   fButtonGroup->SetState(kTRUE);
 //  fExit->SetEnabled();

}

int IntegratedTesterGui::returnDateAndTime(){
   
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    char buffer[80];
    strftime(buffer,80,"%g%m%d%H%M",now);
  return atoi(buffer);
}

void IntegratedTesterGui::DoExit()
{
   WriteInfo("Closed the calibration GUI!");
   logbook.close();
   // Exit this application via the Exit button or Window Manager.
   // Use one of the both lines according to your needs.
   // Please note to re-run this macro in the same ROOT session,
   // you have to compile it to get signals/slots 'on place'.
   //DeleteWindow();            // to stay in the ROOT session
   gApplication->Terminate();   // to exit and close the ROOT session
}

void IntegratedTesterGui::SetGroupEnabled(Bool_t on)
{
   fButtonGroup->SetState(on);
}

std::string IntegratedTesterGui::ReadCompleteFile(std::string filename)
{
  std::ifstream ifs(filename.c_str());
  std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

  return content;
}

void IntegratedTesterGui::WriteInfo(std::string information)
{
   //opening log file
   std::ofstream ofs;
   ofs.open(logPath,std::ofstream::out | std::ofstream::app);
   ofs << time(NULL) << " " << information << std::endl;
   ofs.close();
   std::cout << information << std::endl;
}

void IntegratedTesterGui::WriteResultsTestToDB(int DateAndTime, std::string serialNumber, int status)
{
   std::string serial_number = fTextEntry->GetText();
   std::cout << "serial number that will be written to DB: " << serial_number << std::endl;
   std::ofstream ofs;
   ofs.open(dataBasePath,std::ofstream::out | std::ofstream::app);
   ofs << DateAndTime << "," << serialNumber << "," << status << std::endl;
}
/*
//read the database and checks wether the calibration was succesful

std::string * IntegratedTesterGui::ReadDBLastLine(){

   fstream file(dataBasePath);
   static std::string r[2];
   std::string buffer;
   std::vector<std::string> contents; 
  // std::cout << "checking the database file" << std::endl;
   //reading the last line of the file (TODO: this is not the most efficient way as it saves the entire file in a vector)
   if(file)
   {
       while(getline(file, buffer))
       {
            contents.push_back(buffer);
       }      
    //   std::cout << "last line of the database" << std::endl;
    //   std::cout << contents[contents.size() - 1] << std::endl;
                                      
   }
   //save the info in the last line
   std::vector<std::string> DBLastLine;
   std::istringstream ss(contents[contents.size() - 1]);
   std::string token;
   int i = 0;
   while(std::getline(ss, token, ',')) {
   	if(i == 0){std::cout << "Serial number of the hybrid written to the database: " <<  token << std::endl;
     	}
   	if(i == 1){std::cout << "Status of the test written to the database: " << token << std::endl;
   	}
   r[i] = token;   
   i++;
  // std::cout << "leaving the reading of the DB" << std::endl;
   }
   return r;   
} 
*/  
/*
int IntegratedTesterGui::runIntegratedTester(int nr_CBCs, int dateAndTime){
   //char command[800];
   //std::cout << "dateAndTime: " << dateAndTime << " nr_CBCs: " << nr_CBCs << std::endl; 
   //snprintf( command, 800, "integratedtester -b -o Results/IntegratedTesterFromGUI-%d -f settings/HWDescription_%dCBC.xml --checkRegisters --calibrate --checkShorts --measureOccupancy", (int)dateAndTime, (int)nr_CBCs );
   //std::cout << "the command that will be PARSSED is: " << command << std::endl;
//   int status = system(command);
   std::cout << "**************---------RIGHT BEFORE STARTING THE INTEGRATEDTESTER------------------------*****************" << std::endl;
   int status = integratedtesterForGUI(nr_CBCs);
   std::cout << "THE STATUS FROM THE integratedTester:  " << status << std::endl; 
   std::cout << "*************----------RIGHT AFTER THE INTEGRATEDTESTER----------------------------------*****************" << std::endl;
   return WEXITSTATUS(status); 
   //write the serial number that is scanned and temporarly saved in serial_number.txt AND if the test was a succes (1) or failed (0) to the database.txt file
   //WriteResultsTestToDB(status);	
   
   std::string *lastLine;
   lastLine = ReadDBLastLine();  
   std::string serial_number_database = *(lastLine + 0);
   std::string calStatus_database = *(lastLine + 1);
   //std::cin.get();
   //TODO: add aditional checks to see if the last line really corresponds to the hybrid you are testing!! And it e.g. does not just print that the calibration has succeeded, because it has worked for the previously tested hybrid.
   //std::cout << 'Calibration status read from the database:' << calStatus << std::endl;
   std::string serial_number_scanned = ReadSerialNumberFromFile();
   */	
 /*  if(calStatus_database == '1' && serial_number_database == serial_number_scanned){
      return true;
   }
   else if(serial_number_database != serial_number_scanned){
     // WriteInfo("The serial number in the last entry of the database is different from the serial number of the scanned hybrid. Something went wrong with writing the results from the calibration to the database.");
   //   std::cout << "Serial number in database: " << serial_number_database << std::endl;
   //   std::cout << "Serial number scanned: " << serial_number_scanned << std::endl;
      return false;
   }
   else if(serial_number_database == serial_number_scanned && calStatus_database == '0'){
      //WriteInfo("The last entry in the database was for the scanned hybrid, but the test failed");
      return false;
   }
   else{
      return false;
   }*/   
//}
 /*
void IntegratedTesterGui::HandleReturn()
{
   configXML = fConfigXML->GetText();
   std::cout << configXML << std::endl;
}
*/
/*
void IntegratedTesterGui::DoAlreadyTestedPopUp(){
   //create a new window for pop up
   fPopUp = new TGMainFrame(gClient->GetRoot(),300,300);
   fPopupTopVertical = new TGVerticalFrame(fPopUp,300,300);  
   //add a label to describe what the issue is
   AlreadyTestedPopUpLabel = new TGLabel(fPopupTopVertical, "This hybrid has already been tested!!");
   AlreadyTestedPopUpLabel->SetText("This hybrid has already been tested before!\n Do you want to test it again?");
   AlreadyTestedPopUpLabel->Layout();
   fPopupTopVertical->AddFrame(AlreadyTestedPopUpLabel, new TGLayoutHints(kLHintsExpandX|kLHintsExpandY, 2, 2, 2, 2));  
   
   //add a horizontal frame with two buttons to choose how to proceed
   TGHorizontalFrame *fHorFrameForPopUpButtons = new TGHorizontalFrame(fPopupTopVertical);
   
   fProceed = new TGTextButton(fHorFrameForPopUpButtons, "&Proceed with the test", IDs.GetUnID());
   fProceed->Connect("Clicked()", "IntegratedTesterGui", this, "ClosePopUpAndProceedWithTest()");
   fHorFrameForPopUpButtons->AddFrame(fProceed, new TGLayoutHints(kLHintsCenterY, 2,2,2,2));
   fStartTest->SetToolTipText("Click this button to redo the calibration. An entry will be added for this hybrid in the DB.");
   
   fCancelTest = new TGTextButton(fHorFrameForPopUpButtons, "&Cancel Test", IDs.GetUnID());
   fCancelTest->Connect("Clicked()", "IntegratedTesterGui", this, "ClosePopUp()");
   fHorFrameForPopUpButtons->AddFrame(fCancelTest, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
   fCancelTest->SetToolTipText("Click this button to NOT proceed with the test.");
//add the horizontal layout to the vertical
   fPopupTopVertical->AddFrame(fHorFrameForPopUpButtons,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,2,2,2,2));
//add the vertical layout to the popup window 
   fPopUp->AddFrame(fPopupTopVertical,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,
                                             2,2,2,2)); 

   //Default state
   fPopUp->SetWindowName("Hybrid already tested");
   fPopUp->MapSubwindows();
   fPopUp->Resize(500,500);
   fPopUp->MapWindow();

}

void IntegratedTesterGui::ClosePopUp(){
    //FrameToClose->CloseWindow();
    std::cout << "This should close the PopUp" << std::endl;
    fPopUp->CloseWindow();
}
*/
ClassImp(IntegratedTesterGui);
int main(int argc, char *argv[])
{
   XInitThreads();
   TApplication theApp("App", &argc, argv);
   new IntegratedTesterGui(gClient->GetRoot(),120,120);
   theApp.Run();
   return 0;
}

