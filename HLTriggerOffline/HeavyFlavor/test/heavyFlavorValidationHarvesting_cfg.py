import FWCore.ParameterSet.Config as cms

process = cms.Process('HEAVYFLAVORVALIDATIONHARVESTING')

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    fileMode = cms.untracked.string('FULLMERGE')
)

process.source = cms.Source("PoolSource",
    processingMode = cms.untracked.string('RunsAndLumis'),
    fileNames = cms.untracked.vstring('file:/tmp/heavyFlavorValidation.root')
)

process.load('Configuration/StandardSequences/EDMtoMEAtRunEnd_cff')
process.dqmSaver.dirName = '/tmp/'
#process.DQMStore.referenceFileName = '/tmp/DQM_V0001_R000000001__TProfile_3_1__CMSSW_X_Y_Z__RECO.root'
#process.dqmSaver.referenceHandling = 'all'
process.load('HLTriggerOffline/HeavyFlavor/heavyFlavorValidationHarvestingSequence_cff')

process.edmtome_step = cms.Path(process.EDMtoME)
process.validationHarvesting = cms.Path(process.heavyFlavorValidationHarvestingSequence)
process.dqmsave_step = cms.Path(process.DQMSaver)

process.schedule = cms.Schedule(process.edmtome_step,process.validationHarvesting,process.dqmsave_step)

