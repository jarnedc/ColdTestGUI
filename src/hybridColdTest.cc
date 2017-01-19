#include <cstring>
#include "../HWDescription/Cbc.h"
#include "../HWDescription/Module.h"
#include "../HWDescription/BeBoard.h"
#include "../HWInterface/CbcInterface.h"
#include "../HWInterface/BeBoardInterface.h"
#include "../HWDescription/Definition.h"
//#include "../tools/HybridColdTesting.h"
#include "../Utils/argvparser.h"
#include "TROOT.h"
#include "TApplication.h"
#include "../Utils/Timer.h"
#include "GUI/IntegratedTesterGUI.h"

using namespace Ph2_HwDescription;
using namespace Ph2_HwInterface;
using namespace Ph2_System;

using namespace CommandLineProcessing;

int main( int argc, char* argv[] )
{
	ArgvParser cmd;
	//starting the GUI
	TApplication cApplication("App",&argc, argv);
	IntegratedTesterGUI cGui;
	cApplication.Run();
	return 0;
}
