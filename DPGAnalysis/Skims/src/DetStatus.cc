#include "DPGAnalysis/Skims/interface/DetStatus.h" 
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Scalers/interface/DcsStatus.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <iostream>
 
using namespace std;

//
// -- Constructor
//
DetStatus::DetStatus( const edm::ParameterSet & pset ) {
   verbose_      = pset.getUntrackedParameter<bool>( "DebugOn", false );
   AndOr_      = pset.getParameter<bool>( "AndOr");
   applyfilter_      = pset.getParameter<bool>( "ApplyFilter");
   DetNames_ = pset.getParameter<std::vector<std::string> >( "DetectorType" );

  // build a map
  DetMap_=0;
  for (unsigned int detreq=0;detreq<DetNames_.size();detreq++)
    {
      for (unsigned int detlist=0;detlist<DcsStatus::nPartitions;detlist++)
	{
	  
	  if (DetNames_[detreq]==DcsStatus::partitionName[detlist])
	    {
	      DetMap_|=(1 << DcsStatus::partitionList[detlist]);
	      if (verbose_)
		  std::cout << "DCSStatus filter: asked partition " << DcsStatus::partitionName[detlist] << " bit " << DcsStatus::partitionList[detlist] << std::endl; 

	    }
	}
    }
} 

//
// -- Destructor
//
DetStatus::~DetStatus() {
}
 
bool DetStatus::filter( edm::Event & evt, edm::EventSetup const& es) {
  
  bool accepted=false;

  edm::Handle<DcsStatusCollection> dcsStatus;
  evt.getByLabel("scalersRawToDigi", dcsStatus);

  if (dcsStatus.isValid()) 
    {
      if ((*dcsStatus).size()==0)
	{
	  // it's probably a MC event, accepet it in any case
	  edm::LogError("DetStatus") << "Error! dcsStatus has size 0, accept in any case" ;
	  accepted=true;
	}
      else 
	{
	  unsigned int curr_dcs=(*dcsStatus)[0].ready();
	  std::cout << "curr_dcs = " << curr_dcs << std::endl;
	  if(AndOr_)
	    accepted=((DetMap_ & curr_dcs)== DetMap_);
	  else
	    accepted=((DetMap_ & curr_dcs)!= 0);
	    
	  if (verbose_)

	    {
	      std::cout << "DCSStatus filter: requested map: " << DetMap_ << " dcs in event: " <<curr_dcs << " filter: " << accepted << std::endl; 
	      std::cout << "Partitions ON: " ;
	      for (unsigned int detlist=0;detlist<DcsStatus::nPartitions;detlist++)
		{
		  if ((*dcsStatus)[0].ready(DcsStatus::partitionList[detlist]))
		    {
		      std::cout << " " << DcsStatus::partitionName[detlist];
		    }
		}
	      std::cout << std::endl ;
	    }
	}
    }
  else
    {
      edm::LogError("DetStatus") << "Error! can't get the product: scalersRawToDigi, accept in any case" ;
      accepted=true;
    }

  if (! applyfilter_) accepted=true;
  return accepted;
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(DetStatus);

 
