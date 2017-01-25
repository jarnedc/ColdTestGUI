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

#include "hybridFunctionalTest.h"



   Bool_t calibration_2CBC_started = false;
   Bool_t calibration_8CBC_started = false;
   Bool_t isRunning = false;
   //ClassDef(hybridFunctionalTest, 0)
   ofstream logbook;
   bool debug = false;

hybridFunctionalTest::hybridFunctionalTest(const TGWindow *p, UInt_t w, UInt_t h)
   : TGMainFrame(p, w, h)
{ 
   SetCleanup(kDeepCleanup);
   Connect("CloseWindow()", "hybridFunctionalTest", this, "DoExit()");
   DontCallClose();
   
   //define the Radio buttons
   TGHorizontalFrame *fHL2 = new TGHorizontalFrame(this, 800, 200);
   fButtonGroup = new TGVButtonGroup(fHL2, "Hybrid selection");
   fRadiob[0] = new TGRadioButton(fButtonGroup, new TGHotString("2CBC (this is the small one)"),IDs.GetUnID());
   fRadiob[0]->SetToolTipText("Select this if you want to run the callibration for the 2CBC hybrid. This is the PCB containing 2 CBC chips.");
   fRadiob[1] = new TGRadioButton(fButtonGroup, new TGHotString("8CBC (this is the big one)"),IDs.GetUnID());
   fRadiob[1]->SetToolTipText("Select this if you want to run the callibration for the 8CBC hybrid. This is the PCB containing 8 CBC chips. This is set as default.");
   fButtonGroup->Show();
  
   //define the Start Calibration text button
   TGHorizontalFrame *fHL1 = new TGHorizontalFrame(this, 800, 100, kFixedWidth);
   fCalibration = new TGTextButton(fHL1, "&Start Calibration", IDs.GetUnID());
   fCalibration->Connect("Clicked()", "hybridFunctionalTest", this, "Calibrate()");
   fHL1->AddFrame(fCalibration, new TGLayoutHints(kLHintsExpandX));
   fCalibration->SetToolTipText("Click this button to start the calibration. Depending on which hybrid you selected in the list above (2CBC or 8CBC) it will automatically run with the correct settings");
   AddFrame(fHL1, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,1,1,1,1));


   //define the Redo Calibration text button
   fRedoCalibration = new TGTextButton(fHL1, "&Redo Calibration", IDs.GetUnID());
   fRedoCalibration->Connect("Clicked()", "hybridFunctionalTest", this, "Calibrate()");
   fHL1->AddFrame(fRedoCalibration, new TGLayoutHints(kLHintsExpandX));
   fRedoCalibration->SetToolTipText("Click this button to redo the calibration for the current hybrid.");
   AddFrame(fHL1, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,1,1,1,1));
   fRedoCalibration->SetState(kButtonDisabled);
/*
   // load config XML
   TGHorizontalFrame *fHLXML = new TGHorizontalFrame(this, 300, 200, kFixedWidth);
   fConfigXML = new TGTextEntry(fHLXML, (const char *)"", IDs.GetUnID());
   fConfigXML->SetMaxLength(4096);
   fConfigXML->SetText(configXML.c_str());
   fConfigXML->Connect("ReturnPressed()", "TextViewMainFrame", this, "HandleReturn()");
   fHLXML->AddFrame(new TGLabel(fHLXML, "Configuration XML: "),new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 5, 5, 5, 5));
   fHLXML->AddFrame(fConfigXML, new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));

   fHLXML->AddFrame(fConfigXML, new TGLayoutHints(kLHintsExpandX));
   fConfigXML->SetToolTipText("Configuration file used for calibrations.");
   AddFrame(fHLXML, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,1,1,1,1));
*/

   //define the Exit text button
   TGHorizontalFrame *fHL3 = new TGHorizontalFrame(this, 800, 100, kFixedWidth);
   fExit = new TGTextButton(fHL3, "&Exit this application", IDs.GetUnID());
   fExit->Connect("Clicked()", "hybridFunctionalTest", this, "DoExit()");
   fHL3->AddFrame(fExit, new TGLayoutHints(kLHintsExpandX));
   fExit->SetToolTipText("Click this button if you want to exit this GUI");
   AddFrame(fHL3, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY,1,1,1,1));

   //define the status label
   fGframe = new TGGroupFrame(this, "State of the test",kFitWidth);
   state = new TGLabel(fGframe, "I am waiting for your input", kFitWidth);
   fGframe->AddFrame(state, new TGLayoutHints(kLHintsTop | kLHintsLeft,5, 5, 5, 5));
   AddFrame(fGframe, new TGLayoutHints(kLHintsExpandX, 2, 2, 1, 1));

   //define the serialNumber label
   fGframe2 = new TGGroupFrame(this, "Hybrid Serial number");
   SerialNumberLabel = new TGLabel(fGframe2, "The serial number comes here");
   fGframe2->AddFrame(SerialNumberLabel, new TGLayoutHints(kLHintsTop | kLHintsLeft,5, 5, 5, 5));
   AddFrame(fGframe2, new TGLayoutHints(kLHintsExpandX, 2, 2, 1, 1));
   

   //Default state
   fButtonGroup->SetState(kTRUE);
   SetWindowName("2CBC/8CBC Hybrid calibration");
   MapSubwindows();
   Resize(800,400);
   MapWindow();
   fButtonGroup->SetRadioButtonExclusive(kTRUE);
   fRadiob[1]->SetOn();
};

hybridFunctionalTest::~hybridFunctionalTest()
{
   // Destructor.
   Cleanup();
}

int hybridTypeFromButton(){
   if(fRadiob[0]->IsOn()){
	return 2
   }
   if(fRadiob[1]->IsOn()){
	return 8
   }
}
void hybridFunctionalTest::Calibrate()
{
   isRunning = true;
   fCalibration->SetState(kButtonDisabled);
   fButtonGroup->SetState(kFALSE);
   fRedoCalibration->SetState(kButtonDisabled);
   SerialNumberLabel->SetText(ReadSerialNumberFromFile().c_str());
   gSystem->ProcessEvents();
   if(fRadiob[0]->IsOn()){
      //starting the calibration for 2CBC
      WriteInfo("Starting calibration for 2CBC hybrid");
      //TODO: it does not show this GOING
      state->SetText("ONGOING 1");
      gSystem->ProcessEvents();
      calibration_2CBC_started = true;
      //TODO: should implement that the calibrate function returns a status flag when the calibration was ok or when it was faulty. E.g: returns 0 if everything was OK, returns 1 if there was a problem with the I2C, returns 2 if there was a problem with the GLIB, .... (check:http://stackoverflow.com/questions/8654089/return-value-of-system-in-c)
      //placeholder that executes a script that sleeps (calibration is running) and writes something to the database.txt file if calibration succeeded or not
      int outcome_of_2CBC_cal = runTest(2);
      if(outcome_of_2CBC_cal ==0){
         state->SetText("SUCCESFULL");
         gSystem->ProcessEvents();
      }  
      else{
         state->SetText("FAILED");
         gSystem->ProcessEvents();
      }
 

   }
   else if(fRadiob[1]->IsOn()){
      //starting the calibration for 8CBC:
      WriteInfo("Starting calibration for 8CBC hybrid");
      //TODO: it does not show this GOING
      state->SetText("ONGOING 1");
      gSystem->ProcessEvents();
      //TODO: should implement that the calibrate function returns a status flag when the calibration was ok or when it was faulty. E.g: returns 0 if everything was OK, returns 1 if there was a problem with the I2C, returns 2 if there was a problem with the GLIB, ....
      //placeholder that executes a script that sleeps (calibration is running) and writes something to the database.txt file if calibration succeeded or not
      int outcome_of_8CBC_cal = runTest(8);
      if(outcome_of_8CBC_cal==0){
         state->SetText("SUCCESFULL");
         gSystem->ProcessEvents();
      }  
      else{
         state->SetText("FAILED");
         gSystem->ProcessEvents();
      }
   }
  isRunning = false; 
  fCalibration->SetState(kButtonUp);
  fCalibration->SetText("Start next hybrid calibration");
  fRedoCalibration->SetState(kButtonUp);
  fButtonGroup->SetState(kTRUE);

  gSystem->ProcessEvents();
   
}

void hybridFunctionalTest::DoExit()
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

void hybridFunctionalTest::SetGroupEnabled(Bool_t on)
{
   fButtonGroup->SetState(on);
}

void calibrate_GUI()
{
   new hybridFunctionalTest(gClient->GetRoot(),120,120);
}

void hybridFunctionalTest::WriteInfo(std::string information)
{
   //opening log file
   std::ofstream ofs;
   ofs.open("src/GUI/log.txt",std::ofstream::out | std::ofstream::app);
   ofs << time(NULL) << " " << information << std::endl;
   ofs.close();
   std::cout << information << std::endl;
}

std::string hybridFunctionalTest::ReadSerialNumberFromFile()
{
   //opening serial_number.txt file
  std::string serial_number;
  ifstream myfile ("src/GUI/serial_number.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,serial_number) )
    {
      std::cout << "serial_number from file: " << serial_number << '\n';
    }
    myfile.close();
  }
  else std::cout << "Unable to open serial_number.txt file"; 
  return serial_number;
}
void hybridFunctionalTest::WriteResultsTestToDB(int status)
{
   std::string serial_number;
   ifstream myfile("src/GUI/serial_number.txt");
   if(myfile.is_open())
   {
       while(getline(myfile,serial_number))
         {
            std::cout << "serial number from file: " << serial_number << '\n';
          }
         myfile.close();
   }
   else std::cout << "Unable to open serial_number.txt file";
   std::ofstream ofs;
   ofs.open("src/GUI/database.txt",std::ofstream::out | std::ofstream::app);
   if(status == 0){
   ofs << serial_number << "," << 1 << std::endl;
   } 
   else{
   ofs << serial_number << "," << 0 << std::endl;
   }  
}

//read the database and checks wether the calibration was succesful

std::string * hybridFunctionalTest::ReadDBLastLine(){

   fstream file("src/GUI/database.txt");
   static std::string r[2];
   std::string buffer;
   std::vector<std::string> contents; 
   std::cout << "checking the database file" << std::endl;
   //reading the last line of the file (TODO: this is not the most efficient way as it saves the entire file in a vector)
   if(file)
   {
       while(getline(file, buffer))
       {
            contents.push_back(buffer);
       }      
       std::cout << "last line of the database" << std::endl;
       std::cout << contents[contents.size() - 1] << std::endl;
                                      
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
   std::cout << "leaving the reading of the DB" << std::endl;
   }
   return r;   
} 
  

bool hybridFunctionalTest::run_calibration(int nr_CBCs){
   char command[100];
   if(nr_CBCs==2){
      if(debug == true){
         //placeholder script for the real calibration
         strcpy( command, "python python_placeholder/calibration2CBCplaceholder.py" );
      }
      else{
	//TODO: change this to 2CBC
         strcpy( command, "calibrate -f settings/HWDescription_1CBC_calibration_reference.xml -b" );
      }   
      WriteInfo("Command send to start 2CBC calibration");
         
   }
   if(nr_CBCs==8){
      if(debug == true){
         //placeholder script for the real calibration
         strcpy( command, "python python_placeholder/calibration8CBCplaceholder.py" );
      }
      else{
         strcpy( command, "calibrate -f settings/HWDescription_8CBC.xml -b" );
      }   
      WriteInfo("Command send to start 8CBC calibration");
   }
   int status = system(command); 
   //write the serial number that is scanned and temporarly saved in serial_number.txt AND if the test was a succes (1) or failed (0) to the database.txt file
   WriteResultsTestToDB(status);	
   std::cout << "results test written to DB" << std::endl;
   
   std::string *lastLine;
   lastLine = ReadDBLastLine();  
   std::cout << "start saving the data from last line in the DB to variables" << std::endl;
   std::string serial_number_database = *(lastLine + 0);
   std::string calStatus_database = *(lastLine + 1);
   std::cout << "data from last line in DB saved in variables" << std::endl;
   //std::cin.get();
   //TODO: add aditional checks to see if the last line really corresponds to the hybrid you are testing!! And it e.g. does not just print that the calibration has succeeded, because it has worked for the previously tested hybrid.
   //std::cout << 'Calibration status read from the database:' << calStatus << std::endl;
   std::string serial_number_scanned = ReadSerialNumberFromFile();
   if(calStatus_database == '1' && serial_number_database == serial_number_scanned){
      return true;
   }
   else if(serial_number_database != serial_number_scanned){
      WriteInfo("The serial number in the last entry of the database is different from the serial number of the scanned hybrid. Something went wrong with writing the results from the calibration to the database.");
      std::cout << "Serial number in database: " << serial_number_database << std::endl;
      std::cout << "Serial number scanned: " << serial_number_scanned << std::endl;
      return false;
   }
   else if(serial_number_database == serial_number_scanned && calStatus_database == '0'){
      WriteInfo("The last entry in the database was for the scanned hybrid, but the test failed");
      return false;
   }
   else{
      return false;
   }   
}
/*
void hybridFunctionalTest::HandleReturn()
{
   configXML = fConfigXML->GetText();
   std::cout << configXML << std::endl;
}
*/


int hybridFunctionalTest::runTest(int nrCBCs)
{
	ArgvParser cmd;

	// init
	cmd.setIntroductoryDescription( "CMS Ph2_ACF  calibration routine using K. Uchida's algorithm or a fast algoriithm" );
	// error codes
	cmd.addErrorCode( 0, "Success" );
	cmd.addErrorCode( 1, "Error" );
	// options
	cmd.setHelpOption( "h", "help", "Print this help page" );

	cmd.defineOption( "file", "Hw Description File . Default value: settings/Calibration8CBC.xml", ArgvParser::OptionRequiresValue /*| ArgvParser::OptionRequired*/ );
	cmd.defineOptionAlternative( "file", "f" );

	cmd.defineOption( "output", "Output Directory . Default value: Results", ArgvParser::OptionRequiresValue /*| ArgvParser::OptionRequired*/ );
	cmd.defineOptionAlternative( "output", "o" );

	cmd.defineOption( "skip", "skip scaning VCth vs Vplus", ArgvParser::NoOptionAttribute );

	cmd.defineOption( "old", "Use old calibration algorithm", ArgvParser::NoOptionAttribute );



	cmd.defineOption( "allChan", "Do calibration using all channels? Default: false", ArgvParser::NoOptionAttribute );
	cmd.defineOptionAlternative( "allChan", "a" );

	cmd.defineOption( "batch", "Run the application in batch mode", ArgvParser::NoOptionAttribute );
	cmd.defineOptionAlternative( "batch", "b" );


	//int result = cmd.parse( argc, argv );
	//if ( result != ArgvParser::NoParserError )
	//{
	//	std::cout << cmd.parseErrorDescription( result );
	//	exit( 1 );
	//}

	// now query the parsing results
	std::string cHWFile =  "settings/Calibration8CBC.xml";
	if(nrCBCs = 2){
	 	cHWFile =  "settings/HWDescription_1CBC_calibration_reference.xml";
	}
	std::string cDirectory = "Results/";
	cDirectory += "Calibration";
	bool cVplus = true;

	bool cCalibrateTGrp =  false;
	bool batchMode = true ;


//	TApplication cApp( "Root Application", &argc, argv );
	if ( batchMode ) gROOT->SetBatch( true );
//	else TQObject::Connect( "TCanvas", "Closed()", "TApplication", &cApp, "Terminate()" );

	Timer t;

	t.start();
	HybridFunctionalTesting cCalibration;
	cCalibration.InitializeHw( cHWFile );
	cCalibration.InitializeSettings( cHWFile );
	cCalibration.CreateResultDirectory( cDirectory );
	cCalibration.InitResultFile( "CalibrationResults" );
	cCalibration.StartHttpServer();

	cCalibration.ConfigureHw();
	cCalibration.Initialise( false );
	if ( cVplus ) cCalibration.FindVplus();
	cCalibration.FindOffsets();
	cCalibration.SaveResults();
	t.stop();
	t.show( "Time to Calibrate the system: " );

//	if ( !batchMode ) cApp.Run();

	return 0;
}

int main( int argc, char* argv[] )
{
	calibrate_GUI();
	ArgvParser cmd;

	// init
	cmd.setIntroductoryDescription( "CMS Ph2_ACF  calibration routine using K. Uchida's algorithm or a fast algoriithm" );
	// error codes
	cmd.addErrorCode( 0, "Success" );
	cmd.addErrorCode( 1, "Error" );
	// options
	cmd.setHelpOption( "h", "help", "Print this help page" );

	cmd.defineOption( "file", "Hw Description File . Default value: settings/Calibration8CBC.xml", ArgvParser::OptionRequiresValue /*| ArgvParser::OptionRequired*/ );
	cmd.defineOptionAlternative( "file", "f" );

	cmd.defineOption( "output", "Output Directory . Default value: Results", ArgvParser::OptionRequiresValue /*| ArgvParser::OptionRequired*/ );
	cmd.defineOptionAlternative( "output", "o" );

	cmd.defineOption( "skip", "skip scaning VCth vs Vplus", ArgvParser::NoOptionAttribute );

	cmd.defineOption( "old", "Use old calibration algorithm", ArgvParser::NoOptionAttribute );



	cmd.defineOption( "allChan", "Do calibration using all channels? Default: false", ArgvParser::NoOptionAttribute );
	cmd.defineOptionAlternative( "allChan", "a" );

	cmd.defineOption( "batch", "Run the application in batch mode", ArgvParser::NoOptionAttribute );
	cmd.defineOptionAlternative( "batch", "b" );


	//int result = cmd.parse( argc, argv );
	//if ( result != ArgvParser::NoParserError )
	//{
	//	std::cout << cmd.parseErrorDescription( result );
	//	exit( 1 );
	//}

	// now query the parsing results
	int nrCBCs = hybridTypeFromButton();
	std::string cHWFile =  "settings/Calibration8CBC.xml";
	if(nrCBCs = 2){
	 	cHWFile =  "settings/HWDescription_1CBC_calibration_reference.xml";
	}
	std::string cDirectory = "Results/";
	cDirectory += "Calibration";
	bool cVplus = true;

	bool cCalibrateTGrp =  false;
	bool batchMode = true ;


//	TApplication cApp( "Root Application", &argc, argv );
	if ( batchMode ) gROOT->SetBatch( true );
//	else TQObject::Connect( "TCanvas", "Closed()", "TApplication", &cApp, "Terminate()" );

	Timer t;

	t.start();
	HybridFunctionalTesting cCalibration;
	cCalibration.InitializeHw( cHWFile );
	cCalibration.InitializeSettings( cHWFile );
	cCalibration.CreateResultDirectory( cDirectory );
	cCalibration.InitResultFile( "CalibrationResults" );
	cCalibration.StartHttpServer();

	cCalibration.ConfigureHw();
	cCalibration.Initialise( false );
	if ( cVplus ) cCalibration.FindVplus();
	cCalibration.FindOffsets();
	cCalibration.SaveResults();
	t.stop();
	t.show( "Time to Calibrate the system: " );

//	if ( !batchMode ) cApp.Run();

	return 0;

}
