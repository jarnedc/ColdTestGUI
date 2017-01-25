#include <cstring>
#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <chrono>
#include <thread>
#include <sys/wait.h>
#include "boost/tokenizer.hpp"
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/qi_numeric.hpp>

#include "../HWDescription/Cbc.h"
#include "../HWDescription/Module.h"
#include "../HWDescription/BeBoard.h"
#include "../HWInterface/CbcInterface.h"
#include "../HWInterface/BeBoardInterface.h"
#include "../HWDescription/Definition.h"
#include "../tools/HybridTester.h"
#include "../tools/RegisterTester.h"
#include "../tools/ShortFinder.h"
#include "../tools/AntennaTester.h"
#include "../tools/Calibration.h"
#include "../tools/PedeNoise.h"
#include "../Utils/argvparser.h"
#include "TROOT.h"
#include "TApplication.h"
#include "../Utils/Timer.h"

#ifdef __USBINST__
#include <zmq.hpp>
#include "../../Ph2_USBInstDriver/Utils/zmqutils.h"
#include "../Utils/AppLock.cc"
#include "../../Ph2_USBInstDriver/HMP4040/HMP4040Controller.h"
#include "../../Ph2_USBInstDriver/HMP4040/HMP4040Client.h"
using namespace Ph2_UsbInst;
#endif

using namespace Ph2_HwDescription;
using namespace Ph2_HwInterface;
using namespace Ph2_System;
using namespace CommandLineProcessing;
INITIALIZE_EASYLOGGINGPP
#include "IntegratedTesterGUI.h"



int main(int argc, char *argv[])
{
   TApplication theApp("App", &argc, argv);
   new IntegratedTesterGui(gClient->GetRoot(),120,120);
   theApp.Run();
   return 0;
}

