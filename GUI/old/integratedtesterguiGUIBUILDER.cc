// Mainframe macro generated from application: /usr/local//bin/root.exe
// By ROOT version 5.34/32 on 2017-01-16 11:35:01

#ifndef ROOT_TGDockableFrame
#include "TGDockableFrame.h"
#endif
#ifndef ROOT_TGMenu
#include "TGMenu.h"
#endif
#ifndef ROOT_TGMdiDecorFrame
#include "TGMdiDecorFrame.h"
#endif
#ifndef ROOT_TG3DLine
#include "TG3DLine.h"
#endif
#ifndef ROOT_TGMdiFrame
#include "TGMdiFrame.h"
#endif
#ifndef ROOT_TGMdiMainFrame
#include "TGMdiMainFrame.h"
#endif
#ifndef ROOT_TGButtonGroup
#include "TGButtonGroup.h"
#endif
#ifndef ROOT_TGMdiMenu
#include "TGMdiMenu.h"
#endif
#ifndef ROOT_TGListBox
#include "TGListBox.h"
#endif
#ifndef ROOT_TGNumberEntry
#include "TGNumberEntry.h"
#endif
#ifndef ROOT_TGScrollBar
#include "TGScrollBar.h"
#endif
#ifndef ROOT_TGComboBox
#include "TGComboBox.h"
#endif
#ifndef ROOT_TGuiBldHintsEditor
#include "TGuiBldHintsEditor.h"
#endif
#ifndef ROOT_TGuiBldNameFrame
#include "TGuiBldNameFrame.h"
#endif
#ifndef ROOT_TGFrame
#include "TGFrame.h"
#endif
#ifndef ROOT_TGFileDialog
#include "TGFileDialog.h"
#endif
#ifndef ROOT_TGShutter
#include "TGShutter.h"
#endif
#ifndef ROOT_TGCanvas
#include "TGCanvas.h"
#endif
#ifndef ROOT_TGFSContainer
#include "TGFSContainer.h"
#endif
#ifndef ROOT_TGuiBldEditor
#include "TGuiBldEditor.h"
#endif
#ifndef ROOT_TGColorSelect
#include "TGColorSelect.h"
#endif
#ifndef ROOT_TGButton
#include "TGButton.h"
#endif
#ifndef ROOT_TGFSComboBox
#include "TGFSComboBox.h"
#endif
#ifndef ROOT_TGLabel
#include "TGLabel.h"
#endif
#ifndef ROOT_TGMsgBox
#include "TGMsgBox.h"
#endif
#ifndef ROOT_TRootGuiBuilder
#include "TRootGuiBuilder.h"
#endif
#ifndef ROOT_TGTab
#include "TGTab.h"
#endif
#ifndef ROOT_TGListView
#include "TGListView.h"
#endif
#ifndef ROOT_TGStatusBar
#include "TGStatusBar.h"
#endif
#ifndef ROOT_TGListTree
#include "TGListTree.h"
#endif
#ifndef ROOT_TGuiBldGeometryFrame
#include "TGuiBldGeometryFrame.h"
#endif
#ifndef ROOT_TGToolBar
#include "TGToolBar.h"
#endif
#ifndef ROOT_TRootEmbeddedCanvas
#include "TRootEmbeddedCanvas.h"
#endif
#ifndef ROOT_TCanvas
#include "TCanvas.h"
#endif
#ifndef ROOT_TGuiBldDragManager
#include "TGuiBldDragManager.h"
#endif
#ifndef ROOT_TGSplitter
#include "TGSplitter.h"
#endif
#ifndef ROOT_TGObject
#include "TGObject.h"
#endif

#include "Riostream.h"

void integratedtesterguiGUIBUILDER()
{

   // main frame
   TGMainFrame *fMainFrame1051 = new TGMainFrame(gClient->GetRoot(),10,10,kMainFrame | kVerticalFrame);
   fMainFrame1051->SetName("fMainFrame1051");
   fMainFrame1051->SetLayoutBroken(kTRUE);

   // composite frame
   TGCompositeFrame *fMainFrame693 = new TGCompositeFrame(fMainFrame1051,800,800,kVerticalFrame);
   fMainFrame693->SetName("fMainFrame693");

   // vertical frame
   TGVerticalFrame *fVerticalFrame694 = new TGVerticalFrame(fMainFrame693,796,796,kVerticalFrame);
   fVerticalFrame694->SetName("fVerticalFrame694");

   // horizontal frame
   TGHorizontalFrame *fHorizontalFrame695 = new TGHorizontalFrame(fVerticalFrame694,794,130,kHorizontalFrame);
   fHorizontalFrame695->SetName("fHorizontalFrame695");

   // vertical frame
   TGVerticalFrame *fVerticalFrame696 = new TGVerticalFrame(fHorizontalFrame695,354,408,kVerticalFrame);
   fVerticalFrame696->SetName("fVerticalFrame696");

   // embedded canvas
   TRootEmbeddedCanvas *fRootEmbeddedCanvas697 = new TRootEmbeddedCanvas(0,fVerticalFrame694,350,200,kSunkenFrame);
   fRootEmbeddedCanvas697->SetName("fRootEmbeddedCanvas697");
   Int_t wfRootEmbeddedCanvas697 = fRootEmbeddedCanvas697->GetCanvasWindowId();
   TCanvas *c123 = new TCanvas("c123", 10, 10, wfRootEmbeddedCanvas697);
   fRootEmbeddedCanvas697->AdoptCanvas(c123);
   fVerticalFrame696->AddFrame(fRootEmbeddedCanvas697, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));

   // embedded canvas
   TRootEmbeddedCanvas *fRootEmbeddedCanvas709 = new TRootEmbeddedCanvas(0,fVerticalFrame694,350,200,kSunkenFrame);
   fRootEmbeddedCanvas709->SetName("fRootEmbeddedCanvas709");
   Int_t wfRootEmbeddedCanvas709 = fRootEmbeddedCanvas709->GetCanvasWindowId();
   TCanvas *c124 = new TCanvas("c124", 10, 10, wfRootEmbeddedCanvas709);
   fRootEmbeddedCanvas709->AdoptCanvas(c124);
   fVerticalFrame696->AddFrame(fRootEmbeddedCanvas709, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));

   fHorizontalFrame695->AddFrame(fVerticalFrame696, new TGLayoutHints(kLHintsLeft,2,2,2,2));

   fVerticalFrame694->AddFrame(fHorizontalFrame695, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,1,1,1,1));

   // horizontal frame
   TGHorizontalFrame *fHorizontalFrame721 = new TGHorizontalFrame(fVerticalFrame694,792,129,kHorizontalFrame);
   fHorizontalFrame721->SetName("fHorizontalFrame721");

   // vertical buttongroup frame
   TGVButtonGroup *fVButtonGroup722 = new TGVButtonGroup(fHorizontalFrame721,"Hybrid selection");
   TGRadioButton *fRadioButton723 = new TGRadioButton(fVButtonGroup722,"2CBC (this is the small one)",1);
   fRadioButton723->SetToolTipText("Select this if you want to run the callibration for the 2CBC hybrid. This is the PCB containing 2 CBC chips.");
   fRadioButton723->SetTextJustify(36);
   fRadioButton723->SetMargins(0,0,0,0);
   fRadioButton723->SetWrapLength(-1);
   TGRadioButton *fRadioButton726 = new TGRadioButton(fVButtonGroup722,"8CBC (this is the big one)",2);
   fRadioButton726->SetState(kButtonDown);
   fRadioButton726->SetToolTipText("Select this if you want to run the callibration for the 8CBC hybrid. This is the PCB containing 8 CBC chips. This is set as default.");
   fRadioButton726->SetTextJustify(36);
   fRadioButton726->SetMargins(0,0,0,0);
   fRadioButton726->SetWrapLength(-1);
   fVButtonGroup722->SetRadioButtonExclusive(kTRUE);
   fVButtonGroup722->Resize(788,125);
   fVButtonGroup722->Show();
   fHorizontalFrame721->AddFrame(fVButtonGroup722, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));

   fVerticalFrame694->AddFrame(fHorizontalFrame721, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));

   // vertical frame
   TGVerticalFrame *fVerticalFrame729 = new TGVerticalFrame(fVerticalFrame694,792,129,kVerticalFrame);
   fVerticalFrame729->SetName("fVerticalFrame729");
   TGTextButton *fTextButton738 = new TGTextButton(fVerticalFrame729,"&Exit this application",5,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton738->SetTextJustify(36);
   fTextButton738->SetMargins(0,0,0,0);
   fTextButton738->SetWrapLength(-1);
   fTextButton738->Resize(788,39);
   fTextButton738->SetToolTipText("Click this button if you want to exit this GUI");
   fVerticalFrame729->AddFrame(fTextButton738, new TGLayoutHints(kLHintsCenterY));
   fTextButton738->Connect("Clicked()", 0, 0, "DoExit()");

   // horizontal frame
   TGHorizontalFrame *fHorizontalFrame730 = new TGHorizontalFrame(fVerticalFrame729,788,39,kHorizontalFrame);
   fHorizontalFrame730->SetName("fHorizontalFrame730");
   TGTextButton *fTextButton731 = new TGTextButton(fHorizontalFrame730,"&Start Calibration",3,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton731->SetTextJustify(36);
   fTextButton731->SetMargins(0,0,0,0);
   fTextButton731->SetWrapLength(-1);
   fTextButton731->Resize(97,22);
   fTextButton731->SetToolTipText("Click this button to start the calibration. Depending on which hybrid you selected in the list above (2CBC or 8CBC) it will automatically run with the correct settings");
   fHorizontalFrame730->AddFrame(fTextButton731, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   fTextButton731->Connect("Clicked()", 0, 0, "integratedtester()");
   TGTextButton *fTextButton734 = new TGTextButton(fHorizontalFrame730,"&Redo Calibration",4,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton734->SetTextJustify(36);
   fTextButton734->SetMargins(0,0,0,0);
   fTextButton734->SetWrapLength(-1);
   fTextButton734->Resize(101,22);
   fTextButton734->SetState(kButtonDisabled);
   fTextButton734->SetToolTipText("Click this button to redo the calibration for the current hybrid.");
   fHorizontalFrame730->AddFrame(fTextButton734, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   fTextButton734->Connect("Clicked()", 0, 0, "integratedtester()");
   TGTextButton *fTextButton737 = new TGTextButton(fHorizontalFrame730,"&Draw",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton737->SetTextJustify(36);
   fTextButton737->SetMargins(0,0,0,0);
   fTextButton737->SetWrapLength(-1);
   fTextButton737->Resize(37,22);
   fHorizontalFrame730->AddFrame(fTextButton737, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   fTextButton737->Connect("Clicked()", 0, 0, "DoDraw()");

   fVerticalFrame729->AddFrame(fHorizontalFrame730, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));
   TGTextButton *fTextButton738 = new TGTextButton(fVerticalFrame729,"&Exit this application",5,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton738->SetTextJustify(36);
   fTextButton738->SetMargins(0,0,0,0);
   fTextButton738->SetWrapLength(-1);
   fTextButton738->Resize(788,39);
   fTextButton738->SetToolTipText("Click this button if you want to exit this GUI");
   fVerticalFrame729->AddFrame(fTextButton738, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));
   fTextButton738->Connect("Clicked()", 0, 0, "DoExit()");

   fVerticalFrame694->AddFrame(fVerticalFrame729, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));

   // "Serial Number" group frame
   TGGroupFrame *fGroupFrame743 = new TGGroupFrame(fVerticalFrame694,"Serial Number");
   TGLabel *fLabel744 = new TGLabel(fGroupFrame743,"The serial number comes here");
   fLabel744->SetTextJustify(36);
   fLabel744->SetMargins(0,0,0,0);
   fLabel744->SetWrapLength(-1);
   fGroupFrame743->AddFrame(fLabel744, new TGLayoutHints(kLHintsNormal));

   fGroupFrame743->SetLayoutManager(new TGVerticalLayout(fGroupFrame743));
   fGroupFrame743->Resize(792,65);
   fVerticalFrame694->AddFrame(fGroupFrame743, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));

   // "Test summary" group frame
   TGGroupFrame *fGroupFrame745 = new TGGroupFrame(fVerticalFrame694,"Test summary");
   TGLabel *fLabel746 = new TGLabel(fGroupFrame745,"Summary from test ");
   fLabel746->SetTextJustify(36);
   fLabel746->SetMargins(0,0,0,0);
   fLabel746->SetWrapLength(-1);
   fGroupFrame745->AddFrame(fLabel746, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

   fGroupFrame745->SetLayoutManager(new TGVerticalLayout(fGroupFrame745));
   fGroupFrame745->Resize(792,129);
   fVerticalFrame694->AddFrame(fGroupFrame745, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,2,2,2,2));

   // "Status of the test" group frame
   TGGroupFrame *fGroupFrame741 = new TGGroupFrame(fVerticalFrame694,"Status of the test");
   TGLabel *fLabel742 = new TGLabel(fGroupFrame741,"I am waiting for your input");
   fLabel742->SetTextJustify(36);
   fLabel742->SetMargins(0,0,0,0);
   fLabel742->SetWrapLength(-1);
   fGroupFrame741->AddFrame(fLabel742, new TGLayoutHints(kLHintsNormal));

   fGroupFrame741->SetLayoutManager(new TGVerticalLayout(fGroupFrame741));
   fGroupFrame741->Resize(792,64);
   fVerticalFrame694->AddFrame(fGroupFrame741, new TGLayoutHints(kLHintsNormal));

   fMainFrame693->AddFrame(fVerticalFrame694, new TGLayoutHints(kLHintsNormal));

   fMainFrame1051->AddFrame(fMainFrame693, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
   fMainFrame693->MoveResize(0,0,800,800);

   fMainFrame1051->SetMWMHints(kMWMDecorAll,
                        kMWMFuncAll,
                        kMWMInputModeless);
   fMainFrame1051->MapSubwindows();

   fMainFrame1051->Resize(fMainFrame1051->GetDefaultSize());
   fMainFrame1051->MapWindow();
   fMainFrame1051->Resize(1529,802);
}  

void DoExit()
{
   cout << "Slot DoExit()" << endl; 
}

void integratedtester()
{
   cout << "Slot integratedtester()" << endl; 
}

void DoDraw()
{
   cout << "Slot DoDraw()" << endl; 
}
