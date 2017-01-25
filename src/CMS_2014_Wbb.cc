#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/WFinder.hh"
#include "Rivet/Projections/UnstableFinalState.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Math/LorentzTrans.hh"
#include "Rivet/Math/Constants.hh"
#include <cmath>
#include <vector>

namespace Rivet {


  class CMS_2014_Wbb : public Analysis {
    public:

      /// @name Constructors etc.
      //@{

      /// Constructor
      CMS_2014_Wbb()
	: Analysis("CMS_2014_Wbb")
	{  
  	}

      //@}


    public:

      /// @name Analysis methods
      //@{


      /// Book histograms and initialise projections before the run
      void init() {

	FinalState fs;

/*
WFinder Parameters:
inputfs	Input final state
cuts	charged lepton cuts
pid	type of the charged lepton
minmass,maxmass	(transverse) mass window
missingET	minimal amount of missing ET (neutrinos) required
dRmax	maximum dR of photons around charged lepton to take into account for W reconstruction (only relevant if one of the following are true)
clusterPhotons	whether such photons are supposed to be clustered to the lepton object and thus W mom
trackPhotons	whether such photons should be added to _theParticles
masstype	whether mass window should be applied using m or mT
*/

	addProjection(fs, "FinalState");
	WFinder wefinder(fs, -2.1, 2.1, 30*GeV, PID::ELECTRON, 0.1*GeV, 1000*GeV, 0.1*GeV, 0.1);
	addProjection(wefinder, "wefinder");
	WFinder wmfinder(fs, -2.1, 2.1, 30*GeV, PID::MUON, 0.1*GeV, 1000*GeV, 0.1*GeV, 0.1);
	addProjection(wmfinder, "wmfinder");

	
	addProjection(FastJets(fs, FastJets::ANTIKT, 0.5), "AntiKT05");

	/// Book histograms ---> adjust binning !!!!
	_h_jet_bb_Delta_eta = bookHisto1D("jet_bb_Delta_eta", 25, 0, 4);
	_h_jet_bb_Delta_phi = bookHisto1D("jet_bb_Delta_phi", 50, 0, M_PI);
	_h_jet_bb_Delta_pT = bookHisto1D("jet_bb_Delta_pT", 25,0, 250);
	_h_jet_bb_Delta_R = bookHisto1D("jet_bb_Delta_R", 50, 0, 5);
	_h_jet_b_jet_eta = bookHisto1D("jet_b_jet_eta", 25, -4, 4);
	_h_jet_b_jet_phi = bookHisto1D("jet_b_jet_phi", 50, 0, 2.*M_PI);
	_h_jet_b_jet_pT = bookHisto1D("jet_b_jet_pT", 25, 0, 250);
	_h_jet_bb_eta = bookHisto1D("jet_bb_eta", 25, -4, 4);
	_h_jet_bb_mass = bookHisto1D("jet_bb_mass", 25, 25, 200);
	_h_jet_bb_phi = bookHisto1D("jet_bb_phi", 50, 0, 2.*M_PI);
	_h_jet_bb_pT = bookHisto1D("jet_bb_pT", 25, 0, 250);
	_h_jet_Wbb_Delta_eta = bookHisto1D("jet_Wbb_Delta_eta", 25, 0, 4);
	_h_jet_Wbb_Delta_phi = bookHisto1D("jet_Wbb_Delta_phi", 50, 0, M_PI);
	_h_jet_Wbb_Delta_pT = bookHisto1D("jet_Wbb_Delta_pT", 25, 0, 250);
	_h_jet_Wbb_Delta_R = bookHisto1D("jet_Wbb_Delta_R", 50, 0, 8);

	_h_W_eta = bookHisto1D("W_eta", 25, -4, 4);
	_h_W_mass = bookHisto1D("W_mass", 25, 60, 110);
	_h_W_phi = bookHisto1D("W_phi", 50, 0, 2.*M_PI);
	_h_W_pT = bookHisto1D("W_pT", 25, 0, 250);

	_h_xsec = bookHisto1D("xsec", 1, 0, 1);

      }


      /// Perform the per-event analysis
      void analyze(const Event& event) {
	const double weight = event.weight();

	const double JETPTCUT = 25*GeV;

	const WFinder& wefinder = applyProjection<WFinder>(event, "wefinder");
	const WFinder& wmfinder = applyProjection<WFinder>(event, "wmfinder");

	if (wefinder.empty() && wmfinder.empty()) vetoEvent;

	//const Particle &lepton = !wmfinder.empty() ? wmfinder.constituentLepton() : wefinder.constituentLepton();
	//const Particle &nu = !wmfinder.empty() ? wmfinder.constituentNeutrino() : wefinder.constituentNeutrino();

	//if (lepton.pT()<30 || abs(lepton.eta()>2.1)) vetoEvent;
	//const double mt   = sqrt(2 * lepton.pT() * nu.pT() * (1 - cos(lepton.phi()-nu.phi())));
	//if (mt < 45*GeV) vetoEvent;

	//const double mt = !wmfinder.empty() ? wmfinder.mT() : wefinder.mT();
	//if (mt < 45*GeV) vetoEvent;

	const Jets jets = applyProjection<FastJets>(event, "AntiKT05").jetsByPt(JETPTCUT,MAXDOUBLE, -2.4, 2.4);

	if (jets.size()<2) vetoEvent;

	// Identify the b-jets
	Jets bjets;
	foreach (const Jet& jet, jets) {
	  if (jet.containsBottom() && jet.pT() > JETPTCUT) {
	    bjets.push_back(jet);
	  }
	}
	if(bjets.size()!=2) vetoEvent;


	// W properties
	const Particle w = !wmfinder.empty() ? wmfinder.boson() : wefinder.boson();
	_h_W_phi->fill(w.phi(), weight);
	_h_W_pT->fill(w.pT(), weight);
	_h_W_eta->fill(w.eta(), weight);
	_h_W_mass->fill(w.mass(), weight);


	for (size_t i = 0; i < bjets.size()-1; ++i) {
	  for (size_t j = i+1; j < bjets.size(); ++j) {
	    const Jet& jet1 = bjets[i];
	    const Jet& jet2 = bjets[j];

	    double jetEta;
	    double jetPhi;
	    double jetPt;

	    if ( jet1.pT() > jet2.pT() ){
	      jetEta = jet1.eta();
	      jetPhi = jet1.phi();
	      jetPt = jet1.pT();
	    }
	    else{
	      jetEta = jet2.eta();
	      jetPhi = jet2.phi();
	      jetPt = jet2.pT();
	    }
	    _h_jet_b_jet_eta->fill( jetEta , weight );
	    _h_jet_b_jet_phi->fill( jetPhi , weight );
	    _h_jet_b_jet_pT->fill( jetPt , weight );


	    const double deltaEtaJJ = fabs(jet1.eta() - jet2.eta());
	    const double deltaPhiJJ = deltaPhi(jet1.momentum(), jet2.momentum());
	    const double deltaRJJ = deltaR(jet1.momentum(), jet2.momentum());
	    const double deltaPtJJ = fabs(jet1.pT() - jet2.pT());
	    _h_jet_bb_Delta_eta->fill(deltaEtaJJ, weight);
	    _h_jet_bb_Delta_phi->fill(deltaPhiJJ, weight);
	    _h_jet_bb_Delta_pT->fill(deltaPtJJ, weight);
	    _h_jet_bb_Delta_R->fill(deltaRJJ, weight);

	    const FourMomentum bb = jet1.momentum() + jet2.momentum();
	    _h_jet_bb_eta->fill(bb.eta(), weight);
	    _h_jet_bb_mass->fill(bb.mass(), weight);
	    _h_jet_bb_phi->fill(bb.phi(), weight);
	    _h_jet_bb_pT->fill(bb.pT(), weight);

	    const double deltaEtaWbb = fabs(bb.eta() - w.eta());
	    const double deltaPhiWbb = deltaPhi(bb, w.momentum());
	    const double deltaRWbb = deltaR(bb, w.momentum());
	    const double deltaPtWbb = fabs(bb.pT() - w.pT());
	    _h_jet_Wbb_Delta_eta->fill(deltaEtaWbb, weight);
	    _h_jet_Wbb_Delta_phi->fill(deltaPhiWbb, weight);
	    _h_jet_Wbb_Delta_pT->fill(deltaPtWbb, weight);
	    _h_jet_Wbb_Delta_R->fill(deltaRWbb, weight);
	  }
	}
	 _h_xsec->fill(0.5,weight);	
      }


      /// Normalise histograms etc., after the run
      void finalize() {
	scale(_h_jet_bb_Delta_eta, crossSection()/femtobarn/sumOfWeights());
	scale(_h_jet_bb_Delta_phi, crossSection()/femtobarn/sumOfWeights());
	scale(_h_jet_bb_Delta_pT, crossSection()/femtobarn/sumOfWeights());
	scale(_h_jet_bb_Delta_R, crossSection()/femtobarn/sumOfWeights());
	scale(_h_jet_b_jet_eta, crossSection()/femtobarn/sumOfWeights());
	scale(_h_jet_b_jet_phi, crossSection()/femtobarn/sumOfWeights());
	scale(_h_jet_b_jet_pT, crossSection()/femtobarn/sumOfWeights());
	scale(_h_jet_bb_mass, crossSection()/femtobarn/sumOfWeights());
	scale(_h_jet_bb_eta, crossSection()/femtobarn/sumOfWeights());
	scale(_h_jet_bb_phi, crossSection()/femtobarn/sumOfWeights());
	scale(_h_jet_bb_pT, crossSection()/femtobarn/sumOfWeights());
	scale(_h_jet_Wbb_Delta_eta, crossSection()/femtobarn/sumOfWeights());
	scale(_h_jet_Wbb_Delta_phi, crossSection()/femtobarn/sumOfWeights());
	scale(_h_jet_Wbb_Delta_pT, crossSection()/femtobarn/sumOfWeights());
	scale(_h_jet_Wbb_Delta_R, crossSection()/femtobarn/sumOfWeights());

	scale(_h_W_eta, crossSection()/femtobarn/sumOfWeights());
	scale(_h_W_mass, crossSection()/femtobarn/sumOfWeights());
	scale(_h_W_phi, crossSection()/femtobarn/sumOfWeights());
	scale(_h_W_pT, crossSection()/femtobarn/sumOfWeights());

	scale(_h_xsec,crossSection()/picobarn/sumOfWeights());

      }

      //@}


    private:

      /// @name Histograms
      //@{

      Histo1DPtr _h_jet_bb_Delta_eta, _h_jet_bb_Delta_phi, _h_jet_bb_Delta_pT, _h_jet_bb_Delta_R;
      Histo1DPtr _h_jet_b_jet_eta, _h_jet_b_jet_phi, _h_jet_b_jet_pT;
      Histo1DPtr _h_jet_bb_mass,_h_jet_bb_eta, _h_jet_bb_phi, _h_jet_bb_pT;
      Histo1DPtr _h_jet_Wbb_Delta_eta, _h_jet_Wbb_Delta_phi, _h_jet_Wbb_Delta_pT, _h_jet_Wbb_Delta_R;
      Histo1DPtr _h_W_eta, _h_W_mass, _h_W_phi, _h_W_pT;
      Histo1DPtr _h_xsec;

      //@}

  };


  // This global object acts as a hook for the plugin system
  DECLARE_RIVET_PLUGIN(CMS_2014_Wbb);

}

