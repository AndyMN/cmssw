import FWCore.ParameterSet.Config as cms

from SimTracker.TrackAssociatorProducers.quickTrackAssociatorByHits_cfi import *
from Validation.RecoTrack.TrackValidation_cff import *
quickTrackAssociatorByHits.associateStrip = False
quickTrackAssociatorByHits.associatePixel = False
quickTrackAssociatorByHits.useClusterTPAssociation = False
#TrackAssociatorByHitsRecoDenom.ROUList = ['famosSimHitsTrackerHits']
trackValidator.useLogPt=cms.untracked.bool(True)
trackValidator.dodEdxPlots = False
trackValidator.doPVAssociationPlots = False
trackValidator.sim = [cms.InputTag('famosSimHits','TrackerHits')]

trackValidator.stableOnlyTP = True
trackValidator.histoProducerAlgoBlock.generalTpSelector.stableOnly = True
trackValidator.histoProducerAlgoBlock.TpSelectorForEfficiencyVsEta.stableOnly = True
trackValidator.histoProducerAlgoBlock.TpSelectorForEfficiencyVsPhi.stableOnly = True
trackValidator.histoProducerAlgoBlock.TpSelectorForEfficiencyVsPt.stableOnly = True
trackValidator.histoProducerAlgoBlock.TpSelectorForEfficiencyVsVTXR.stableOnly = True
trackValidator.histoProducerAlgoBlock.TpSelectorForEfficiencyVsVTXZ.stableOnly = True

###must be commented in normal running
###multiTrackValidator.outputFile='validationPlots.root'

tracksValidationStandalone.remove(trackValidatorFromPVStandalone)
tracksValidationStandalone.remove(trackValidatorFromPVAllTPStandalone)
tracksValidationStandalone.remove(trackValidatorAllTPEfficStandalone)
