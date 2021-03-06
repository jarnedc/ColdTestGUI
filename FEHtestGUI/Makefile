ANTENNADIR=../CMSPh2_AntennaDriver
AMC13DIR=/opt/cactus/include/amc13
USBINSTDIR=../../Ph2_USBInstDriver
ZMQ_HEADER_PATH = /usr/include/zmq.hpp
 
CC              = gcc
CXX             = g++
CCFlags         = -g -O0 -w -Wall -pedantic -pthread -std=c++0x -fPIC 
CCFlagsRoot	= `root-config --cflags --glibs`
ROOTVERSION := $(shell root-config --has-http)

HttpFlag = -D__HTTP__
ZmqFlag = -D__ZMQ__
USBINSTFlag     = -D__USBINST__
Amc13Flag     = -D__AMC13__
AntennaFlag = -D__ANTENNA__

DevFlags        =

LibraryDirs = /opt/cactus/lib ../lib  
	IncludeDirs     =  /opt/cactus/include   
	ExternalObjects= $(LibraryPaths) -l iowkit -lcactus_extern_pugixml -lcactus_uhal_log -lcactus_uhal_grammars -lcactus_uhal_uhal -lboost_system -lPh2_Interface -lPh2_Description -lPh2_System -lPh2_Utils -lPh2_Tracker -lPh2_Tools -lpthread -I/usr/include/cppconn -L/usr/lib -lmysqlcppconn  

##################################################
## check if the Root has THttp
##################################################
ifneq (,$(findstring yes,$(ROOTVERSION)))
	ExtObjectsRoot += $(RootLibraryPaths) -lRHTTP $(HttpFlag)
else
	ExtObjectsRoot += $(RootLibraryPaths) 
endif

##################################################
## check if the Antenna driver is installed
##################################################
ifneq ("$(wildcard $(ANTENNADIR))","")
	IncludeDirs += $(ANTENNADIR)
	LibraryDirs += $(ANTENNADIR)/lib /usr/lib64/ 
	#ExternalObjects += -lboost_thread -lPh2_Antenna $(AntennaFlag) 
	ExternalObjects += -lPh2_Antenna $(AntennaFlag) 
	ANTENNAINSTALLED = yes
else
	ANTENNAINSTALLED = no
endif

##################################################
## check if the AMC13 drivers are installed
##################################################
ifneq ("$(wildcard $(AMC13DIR))","")
	ExternalObjects += -lcactus_amc13_amc13 -lPh2_Amc13
	AMC13INSTALLED = yes
else
	AMC13INSTALLED = no
endif

#################################################
# check if ZMQ library is available on this machine
# #################################################
# ifneq ("$(wildcard $(ZMQ_HEADER_PATH))","")
#         ExternalObjects += -lzmq $(ZmqFlag)
#                 ZMQINSTALLED = yes
#                 else
#                 		ZMQINSTALLED = no
#                 		        ZMQINSTRUCTIONS = ZeroMQ library is required to build the lvSupervisor with the server option - get it with \'sudo yum install zeromq-devel\'
#                 		        endif
#
#                 		        ##################################################
## check if the Ph2_USBInstDriver drivers are installed
##################################################
ifneq ("$(wildcard $(USBINSTDIR))","")
	LibraryDirs += $(USBINSTDIR)/lib $(USBINSTDIR)/Utils $(USBINSTDIR)/HMP4040
	IncludeDirs += $(BOOST_INCLUDE) $(USBINSTDIR)/HMP4040 $(USBINSTDIR)/Utils $(USBINSTDIR)/Drivers 
	ExternalObjects += -lpthread -lboost_thread -lPh2_HMP4040 -lPh2_USBUtils -lPh2_Drivers $(USBINSTFlag)
	USBINSTLIBINSTALLED = yes
else
	USBINSTLIBINSTALLED = no
endif

IncludePaths            = $(IncludeDirs:%=-I%)
RootLibraryDirs = /usr/local/lib/root

LibraryPaths = $(LibraryDirs:%=-L%) 
RootLibraryPaths = $(RootLibraryDirs:%=-L%)


binaries	= FEHTesterGUI  
Objs            = dbHandler.o FEHTester.o

.PHONY: clean all 
#all: FEHTesterGUIDict.cc dbHandler.o FEHTester.o FEHTesterGUIDict.o FEHTesterGUI
all: FEHTesterGUIDict.cc dbHandler.o FEHTester.o libPh2_fehGUI.so FEHTesterGUI
rootflags:
	$(eval CCFlags += $(CCFlagsRoot))
	$(eval ExternalObjects += $(ExtObjectsRoot))

noroot: clean $(binariesNoRoot)

print:
	@echo '****************************'
	@echo 'Building executables in FEHtesterGUI/'
	@echo 'Root Has Http:' $(ROOTVERSION)
	@echo 'Amc13 SW installed:' $(AMC13INSTALLED)
	@echo 'Antenna installed:' $(ANTENNAINSTALLED)
	@echo 'Ph2_USBInstDriver installed:' $(USBINSTLIBINSTALLED)
	@echo 'ZeroMQ installed:' $(ZMQINSTALLED)
	@echo '****************************'

FEHTesterGUIDict.cc: FEHTesterGUI.h LinkDef.h
	rootcint -f $@ -c $^

dbHandler.o: dbHandler.cc dbHandler.h 
	$(CXX) -std=c++11  $(DevFlags) $(CCFlags) $(CCFlagsRoot) $(UserCCFlags) $(CCDefines) $(IncludePaths) $(LibraryPaths) $(ExternalObjects) $(RootLibraryPaths) $(ExtObjectsRoot) -c -o $@ $<

FEHTester.o: FEHTester.cc FEHTester.h 
	$(CXX) -std=c++11  $(DevFlags) $(CCFlags) $(CCFlagsRoot) $(UserCCFlags) $(CCDefines) $(IncludePaths) $(LibraryPaths) $(ExternalObjects) $(RootLibraryPaths) $(ExtObjectsRoot) -c -o $@ $<

libPh2_fehGUI.so: FEHTesterGUIDict.cc $(Objs) 
	$(CC) -std=c++0x -shared -o $@ $^ -pthread  $(DevFlags) $(CCFlags) $(CCFlagsRoot) $(UserCCFlags) $(CCDefines) $(IncludePaths) $(LibraryPaths) $(ExternalObjects) $(RootLibraryPaths) $(ExtObjectsRoot)
	cp $@ ../lib/.

FEHTesterGUI: FEHTesterGUI.cc
	$(CXX)  $(CCFlags) -o $@ $< -lPh2_fehGUI  $(IncludePaths) $(ExternalObjects) $(CCFlagsRoot) -lColdBoxDriver -lColdBoxExternalDrivers /opt/picoscope/lib/libusbtc08.so
	cp $@ ../bin

clean:
	rm -f $(binaries) *.o *.so

