#!/bin/bash

FOLDERS=(B C D E Fe Fl G H)
TRIGGERS=(HLT_PFJet40 HLT_PFJet60 HLT_PFJet80 HLT_PFJet140 HLT_PFJet200 HLT_PFJet260 HLT_PFJet320 HLT_PFJet400 HLT_PFJet450) # HLT_PFJet500)

NORMTAG=/afs/cern.ch/user/h/hsiikone/work/Normtags/normtag_PHYSICS.json

PILEUP=/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt
MAXPU=80
XSECS=(69200 80000)

for loc in ${FOLDERS[@]}; do
    echo "Starting loop"
    for XSEC in ${XSECS[@]}; do
        TARGET=puhists/${loc}
        if [[ "$XSEC" -eq "80000" ]]; then
            TARGET=puhists80/${loc}
        fi
        mkdir -p ${TARGET}

        cd ${loc}z
        echo "Trigger HLT_ZeroBias"
        TAG=clumis_ZB
        brilcalc lumi --normtag $NORMTAG -i clumis.json -b "STABLE BEAMS" --hltpath "HLT_ZeroBias_v*" --byls --minBiasXsec $XSEC -o ${TAG}.csv
        wait
        pileupReCalc_HLTpaths.py -i ${TAG}.csv --inputLumiJSON $PILEUP -o ${TAG}_pileup.txt --runperiod Run2
        wait
        pileupCalc.py -i clumis.json --inputLumiJSON ${TAG}_pileup.txt --calcMode true --minBiasXsec $XSEC --maxPileupBin ${MAXPU} --numPileupBins ${MAXPU} ../${TARGET}/HLT_PFJet0.root
        wait
        rm ${TAG}*
        wait
        cd ../$loc
        for trg in ${TRIGGERS[@]}; do
            echo "Trigger "${trg}
            TAG=clumis_${trg}
            brilcalc lumi --normtag $NORMTAG -i clumis.json -b "STABLE BEAMS" --hltpath "${trg}_v*" --byls --minBiasXsec $XSEC -o ${TAG}.csv
            wait
            pileupReCalc_HLTpaths.py -i ${TAG}.csv --inputLumiJSON $PILEUP -o ${TAG}_pileup.txt --runperiod Run2
            wait
            pileupCalc.py -i clumis.json --inputLumiJSON ${TAG}_pileup.txt --calcMode true --minBiasXsec $XSEC --maxPileupBin ${MAXPU} --numPileupBins ${MAXPU} ../${TARGET}/${trg}.root
            wait
            rm ${TAG}*
            wait
        done
        cd ..
    done

    echo "Finished! folder "$loc
done

exit 0
