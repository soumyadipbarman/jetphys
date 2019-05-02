// Purpose: Analysis settings for jet physics package
// Author:    mikko.voutilainen@cern.ch
// Co-author: hannu.siikonen@cern.ch
// Created: June 1, 2015

#ifndef STNGS
#define STNGS

#include <map>
#include <vector>
#include <array>
#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <streambuf>

using std::map;
using std::vector;
using std::array;
using std::set;
using std::string;
using std::cout;
using std::endl;
using std::regex;

// Will assert be used in the programs? More than 1/3 reduction of run time if off.
// CAUTION: this is an expert option - comment this out if you are certain that no problems occur.
#define USEASSERT
// New handling for triggers etc. - comment this out if old mode is to be used
#define NEWMODE

namespace jp {
  constexpr bool strings_equal(char const * a, char const * b) {
    return *a == *b and (*a == '\0' or strings_equal(a + 1, b + 1));
  }

  // Debugging info
  constexpr bool debug = false;
 
  // Use output-MC-1 instead of MC-2b (or NLOxNP) in dagostini.C
  constexpr bool dagfile1 = true;
 
  // Save git version info (recommended)
  constexpr bool gitinfo = true;

  //{ BEGIN fundamental file settings
  // Do we use CHS jets? ("CHS" for yes, "", for legacy/no)
  constexpr const char* chs = "CHS";
  // Algorithm to use ("AK4PF" or "AK8PF" + "chs" for chs jets)
  constexpr const char* algo = "AK4PFchs";
  // Data type ("DATA", "MC", "HW", or "NU")
  constexpr const char* type = "MC";
  // In case of DATA, choose run (all options given in dtfiles).
  // This also affects the hot zone cuts done in MC.
  // The naming format is "RunX...", where X should be chosen correctly.
  constexpr const char* run = "RunD";
  // In case of flat MC, choose file (all options given in mcfiles)
  constexpr const char* mcfile = "P8CP5"; //"P8M1" or "P8CP5"
  constexpr const char* hwfile = "HS1";
  constexpr const char* nufile = "NuGun";
  // Do we use pthatbinned MC (if not, we use flat)
  constexpr bool pthatbins = false;

  const unsigned int   yid = 3; // 0:2016, 1:2017, 2:2017 LowPU, 3:2018
  const unsigned int   yrs = 4; // Number of supported Run years

  // Quick fix for reweightning
  int refidx = 10; // 9 for jt500
<<<<<<< HEAD
  int runidx = 3; // 0-8 for 2016
  
=======
  int runidx = 0; // 0-8 for 2016

>>>>>>> c40ba7d89f0dc9d958f71c1c34d28381f9fa03b7
  // Luminosity weighting options (DATA)
  // Do we use trigger lumi weighting (see triglumi or triglumiera)
  constexpr bool usetriglumi = true;
  // Use per-era values in HistosNormalize (not recommmended)
  // That is, use values from the correct triglumiera instead of triglumi values.
  constexpr bool usetriglumiera = false;
  // Do a "psuedo-weighting" procedure within histosFill.
  // When this setting is on, we weight by w_era/w_year (pseudo-weight) in HistosFill.
  // Then, in HistosNormalize we apply w_year.
  constexpr bool useeraweights = true;
  // So, what is the difference between usetriglumiera and useeraweights?
  // The former applies the correction within HistosNormalize.
  // The latter runs a per-run correction within HistosFill and then further applies the common correction in HistosNormalize.
  // This allows us to "glue" output-*-1.root files together, if several runs are given at the same time.
  // Thus, with the latter option we have a "per-Era" kind of weighting procedure - and all the files behave quite as normally.
  // In HistosFill we apply only small corrections that revolve around one, which is basically just fine-tuning.
  //} END fundamental settings


  //{ BEGIN run settings
  // Number of events to process (-1 for all)
  constexpr Long64_t nentries =
  -1; // all
  //10; // debug
  //100; //debug
  //1000;
  //10000; // shorter test run
  //100000; // short test run
  //1000000; // shortish test run
  //2500000; // shortish test run
  //10000000;
  // Number of events to skip from the beginning (for debugging)
  constexpr Long64_t nskip = 0;
  // Step between events
  constexpr Long64_t skim = 0; // "prescale", off if zero
  // Only load selected branches (large speedup, but be careful!)
  constexpr bool quick = true;
  // Save the infos at times. Setting this to true might help with long runs. (Not recommended)
  constexpr bool save = false;
  //} END run settings

  // Simple helper
  constexpr bool isdt = strings_equal(type,"DATA");
  constexpr bool ismc = !isdt;
  constexpr bool ispy = strings_equal(type,"MC");
  constexpr bool ishw = strings_equal(type,"HW");
  constexpr bool isnu = strings_equal(type,"NU");

  //{ BEGIN A group of constexpr switches and their settings to turn some parts of the code on/off
  // If the output files grow too much, processing becomes more difficult.

  // Produce run-level histograms
  constexpr bool doRunHistos = false; // Not needed very often
  // Produce basic set of histograms
  constexpr bool doBasicHistos = true;
  // Produce full-eta TH3 histograms
  constexpr bool doEtaHistos = true;
  // Special reco/gen histos in mc
  constexpr bool doEtaHistosMcResponse = false; // Special studies
  // Toggle 3D asymmetry and mpf histos off, if too much space is consumed
  constexpr bool do3dHistos = true;
  // Toggle phi histograms
  constexpr bool doPhiHistos = false;
  // Toggle development histos
  constexpr bool doMpfHistos = false;

  // QGL studies by Ozlem (use an external file for qgl studies)
  constexpr bool doqglfile = false;
  constexpr const char qglfile[] = "output-DATA_RunGfullpart-1.root";

  // At some point of time Kostas stored UNCORRECTED four-vector. Current status: CORRECTED
  // NOTE: this is a source of constant anxiety, should be rechecked from time to time
  constexpr bool undojes = true;
  // We can choose also not to apply the new jes onto a four-vector
  constexpr bool redojes = true;
  // For debugging
  constexpr bool skipl2l3res = false;

  // Reapply json selection based on the latest one (check lumicalc if false!).
  constexpr bool dojson = true;
  const constexpr array<const char*,yrs> json_ = {
    "lumicalc/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt",
    "lumicalc/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1mod.txt",
    "lumicalc/Cert_306896-307082_13TeV_EOY2017ReReco_Collisions17_JSON_LowPU.txt",
    "lumicalc/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt"
  };
  const constexpr char* json = json_.at(yid);

  // Calculate luminosity on the fly based on .csv file and take only events with non-zero luminosity.
  constexpr bool dolumi = true;
  const constexpr array<const char*,yrs> lumifile_ = {
    "lumicalc/lumibyls16.csv",
    "lumicalc/lumibyls17.csv",
    "lumicalc/lumibyls17h.csv",
    "lumicalc/lumibyls18.csv"
  };
  const constexpr char* lumifile = lumifile_.at(yid);

  // Decide whether or not to simulate triggers from MC (this is slow)
  constexpr bool domctrigsim = true;
  // Use "mc" trigger for whole pT range instead of stiching triggers together in HistosCombine (false requires trigsim)
  constexpr bool usemctrig = false;

  const array<vector<const char*>,yrs> triggers_ = {{
    {"jt0","jt40","jt60","jt80","jt140","jt200","jt260","jt320","jt400","jt450"},
    {"jt0","jt40","jt60","jt80","jt140","jt200","jt260","jt320","jt400","jt450","jt500"},
    {"jt0","jt15","jt25","jt40","jt60","jt80","jt140"},
    {"jt0","jt40","jt60","jt80","jt140","jt200","jt260","jt320","jt400","jt450","jt500"}
  }};
  const vector<const char*> triggers = triggers_.at(yid);
  const unsigned int notrigs = triggers.size();

  // reference trigger for PU profile in the mc folder and for trigger lumi weighting
  constexpr const array<const char*,yrs> reftrig_ = {
    "jt450",
    "jt500",
    "jt140",
    "jt500"
  };
  constexpr const char* reftrig = reftrig_.at(yid);

  // Thresholds for the corresponding triggers (same as in trigger name)
  const array<vector<double>,yrs> trigthr_ = {{
    {0,40,60,80,140,200,260,320,400,450    },
    {0,40,60,80,140,200,260,320,400,450,500},
    {0,15,25,40,60,80,140},
    {0,40,60,80,140,200,260,320,400,450,500}
  }};
  const vector<double> trigthr = trigthr_.at(yid);

  // Trigger ranges (differ from thresholds)
  const array<vector<array<double,2>>,yrs> trigranges_ = {{
    {{{0,49},{49,84},{84,114},{114,196},{196,272},{272,330},{330,395},{395,468},{468,548},{548,6500}          }},
    {{{0,49},{49,84},{84,114},{114,196},{196,272},{272,330},{330,395},{395,468},{468,548},{548,686},{686,6500}}},
    {{{0,28},{28,37},{37,49},{49,84},{84,114},{114,196},{196,272}}},
    {{{0,64},{64,84},{84,114},{114,196},{196,272},{272,330},{330,395},{395,468},{468,548},{548,686},{686,6500}}}
  }}; // V[5,6], AK4
  const vector<array<double,2>> trigranges = trigranges_.at(yid);

  // Trigger lumis for weighting in /ub
  const array<vector<double>,yrs> triglumi_ = {{
  // ZB         PFJ40      PFJ60       PFJ80       PFJ140       PFJ200        PFJ260        PFJ320         PFJ400         PFJ450          PFJ500
    { 29036.821,250019.11 , 676345.122,2602658.803,22609385.05 , 96089534.929,559334225.38 ,1663980103.656,4870543838.98 ,34184232596.775                },
    { 75086.268,340487.186, 998075.452,4171433.311,39740193.824,218749681.165,555199860.716,1407215678.758,4213837750.579,10451819594.184,41521111348.432},
    {     1.   ,     1.   ,      1.   ,      1.   ,       1.   ,        1.   ,        1.}, // H Dummy values
    { 75831.608,231122.765, 764683.719,4998554.8 ,46417090.061,199877328.665,455315402.462,1751671521.33 ,3618303294.319, 7193355038.764,57269453309.189}
    }}; // in /ub
  const vector<double> triglumi = triglumi_.at(yid);

    // These are used to find out which year and which era we are living in
    const array<vector<regex>,yrs> eras_ = {{
      {regex("^RunB"),regex("^RunC"),regex("^RunD"),regex("^RunE"),regex("^RunFe"),regex("^RunFl"),regex("^RunG"),regex("^RunH")},
      {regex("^RunB"),regex("^RunC"),regex("^RunD"),regex("^RunE"),regex("^RunF")},
      {regex("^RunH[a-zA-Z0-9_]*Fwd$"),regex("^RunH")},
      {regex("^RunA"),regex("^RunB"),regex("^RunC"),regex("^RunD")}
    }};
    const vector<regex> eras = eras_.at(yid);
  // CAUTION: The next are expert options and better to leave untouched if one does not know exactly what is going on.
  // Overrides the above routines with a more intricate weighting scheme. When this is on, output-*1.root is weighted to match the era results.
  // In the version treatment we give the weights directly to induce better comparability
  // Values given in /ub
  const array<vector<vector<double>>,yrs> triglumiera_ = {{
  // 2016 values: (zb,jt40-jt450)
    {{
  //   ZB        PFJ40     PFJ60      PFJ80       PFJ140      PFJ200       PFJ260        PFJ320        PFJ400         PFJ450              Era
      {12272.564,42777.404,154339.679,1013725.894,6678362.048,31439255.077,138379573.748,423036630.016,1156112123.522,5780974274.166}, // B
      { 1267.369,21826.26 , 62136.999, 197392.975,2000961.79 ,10062309.79 , 48166077.979,135218220.578, 412946722.943,2573399420.069}, // C
      { 1898.671,36624.724,104611.27 , 328062.586,3357266.779,16824336.184, 76550163.736,225203181.004, 683469876.284,4248383597.366}, // D
      { 3011.27 ,31294.62 , 86426.534, 270224.019,2763649.831,13071806.045, 65431121.382,191469713.187, 583096480.718,4008663475.924}, // E
      { 1504.894,21653.271, 48745.957, 136195.575,1491075.627, 6052884.716, 38701199.163,116084466.056, 348342950.9  ,2704118419.004}, // Fe
      {  215.493, 2828.924,  7205.162,  18382.409, 204124.035,  681254.62 ,  6502077.341, 18270869.363,  53084258.548, 397499983.002}, // Fl
      { 3165.916,48839.939,123669.326, 370518.873,3628983.85 ,11996221.263,102627755.009,310855295.835, 921468153.924,7540487746.602}, // G
      { 5700.644,58972.432,131684.466, 398826.083,3841266.079,12723493.628,111360342.779,333826688.043, 982546425.482,8605689857.939}  // H
    }},
  // 2017 values: (zb,jt40-jt500)
    {{
  //   ZB         PFJ40      PFJ60      PFJ80       PFJ140       PFJ200        PFJ260        PFJ320        PFJ400         PFJ450         PFJ500               Era
      {  7539.226, 96664.998, 26622.936, 189826.043,12534821.364,100732085.583, 86579973.307,217989804.268, 850535229.404,4433502069.149, 4793979607.968}, // B
      { 12918.576, 57596.329,229617.920,2205841.654, 7557872.755, 31535667.322,134501668.374,335987447.077,1010919949.001,1746883754.461, 9631323656.448}, // C
      {  9652.826, 48475.568,209759.897, 386611.391, 4041221.865, 15774605.427, 70855229.555,180113633.815, 483431612.818, 887087743.403, 4247564824.502}, // D
      { 18436.289, 65480.301,273870.786, 602425.276, 6245719.204, 25002871.020,110449169.249,280091604.472, 761298045.169,1355996073.006, 9313989713.752}, // E
      { 26539.351, 72269.990,258203.913, 786728.947, 9360558.636, 45704451.813,152813820.231,393033189.126,1107652914.187,2028349954.165,13534253545.762}, // F
    }},
  // 2017 RunH values (dummy)
    {{
  //   ZB         HIPFJ15(FWD) HIPFJ25(FWD) HIPFJ40(FWD) HIPFJ60(FWD) HIPFJ80(FWD) HIPFJ140(FWD)
      {   202.798,   16787.739,  141082.702, 2104185.471, 7462468.196,45397276.568,199414408.843}, // H FWD
      {   202.798,   11702.608,   70534.718,  449652.826, 2016829.117, 6734615.464,199413819.206}  // H
    }},
  // 2018 values: (zb,jt40-jt500)
    {{
  //   ZB         PFJ40      PFJ60      PFJ80       PFJ140       PFJ200        PFJ260        PFJ320        PFJ400         PFJ450         PFJ500               Era
<<<<<<< HEAD

      { 25013.934, 66295.974, 89414.136,2456363.426,10191358.171, 44630018.263,116215006.966,399701370.502, 915840136.381,1789905866.607,14052199937.969}, // A
      { 10986.42 , 26966.089,110846.903, 417305.989, 5875972.082, 25182737.494, 55423451.676,221693806.705, 443387613.41 , 886775226.82 , 7094201814.561}, // B
      {  8067.627, 27798.754,108386.566, 408043.543, 5681358.29,  24348565.549, 55309473.888,217862956.528, 434600933.381, 868076887.087, 6936740238.969}, // C
=======
      { 24886.109, 65937.99,  89100.785,2453432.502,10135979.76 , 44392687.158,115825842.173,398144553.92 , 912726818.03 ,1783679072.5  ,14002382122.174}, // A
      { 10979.168, 26940.560,110806.544, 417154.048, 5874327.302, 25175688.436, 55403271.989,221613087.956, 443226175.913, 886452351.826, 7091618814.605}, // B
      { 8067.627, 27798.754,108386.566, 408043.543, 5681358.29, 24348565.549, 55309473.888,217862956.528, 434600933.381, 868076887.087, 6936740238.969}, // C
>>>>>>> c40ba7d89f0dc9d958f71c1c34d28381f9fa03b7
      { 31763.627,110061.948,456036.114,1716841.842,24668401.518,105716007.359,228367469.932,912413387.595,1824474611.147,3648597058.250,29186311317.690}  // D
    }}
  }};
  const vector<vector<double>> triglumiera = triglumiera_.at(yid);

  //{ JEC and IOV settings. In the modern world we have a group of IOV's for which different corrections are applied.
  // https://github.com/cms-jet/JECDatabase/tree/master/tarballs
  const array<string,yrs> jecgt_ = {
    "Summer16_07Aug2017",
    "Fall17_17Nov2017",
    "Fall17_17Nov2017",
    "Autumn18_RunD_V10_MC/Autumn18_Run"
  };
  const string jecgt = jecgt_.at(yid);
  const array<string,yrs> jecversdt_ = {
    "_V18",
    "_V11",//"_V32",
    "_V32",
    "_V10"
  };
  const string jecversdt = jecversdt_.at(yid);
  const array<string,yrs> jecversmc_ = {
    "_V15",
    "_V11",//"_V32",
    "_V32",
    "_V10"
  };
  const string jecversmc = jecversmc_.at(yid);

  // Use Intervals-Of-Validity for JEC
  constexpr const bool useIOV = true ;
  const array<vector<string>,yrs> IOVnames_ = {{
    {"BCD","EF","GH"},
    {"B","C","D","E","F"},
    {"F"}, // Run2017F is used for Run2017H (lowpu)
    //    {"F","F","F","F"} // Run2017F is used for all 2018
    {"A","B","C","D"}
  }};
  const vector<string> IOVnames = IOVnames_.at(yid);
  // Trigger IOVs: the 1 for -inf and 400000 for inf (currently)
  const array<vector<array<int,2>>,yrs> IOVranges_ = {{
    { {272760,276811},{276831,278801},{278802,284045} }, // BCD, EF(early), (Flate)GH
    { {297020,299329},{299337,302029},{302030,303434},{303435,304826},{304911,306460} }, // B,C,DE,F: DE fused at 303434},{303435,
    { {306926,307082} }, // H
    { {315000,316999},{317000,319499},{319500,320399},{320400,400000} } // A,B,C,D
  }};
  const vector<array<int,2>> IOVranges = IOVranges_.at(yid);
  //} END JES and JEC


  //{ BEGIN For MC reweighting purposes, PU profiles for data and MC
  constexpr bool reweighPU = true;
  constexpr const char* pudata = "pileup/curr/pileup_DT.root";
  constexpr const char* pumc   = "pileup/curr/pileup_MC.root";
  constexpr const char* puhw   = "pileup/curr/pileup_HW.root";
  constexpr const char* punu   = "pileup/curr/pileup_NU.root";
  constexpr const double maxpu = 80.0;
  //} END PU profiles

  //{ BEGIN DT/MC: File options

  constexpr const char* filepath = "/media/lmartika/LaCie/";
  //constexpr const char* filepath = "root://eoscms.cern.ch//eos/cms/store/group/phys_smp/Multijet/13TeV/";

    //{ BEGIN DT: Files
    constexpr const array<const char*,yrs> dtpath_ =
      {"Data/2016/Final/","2017/Mar18ReRecoMINIAOD/","Data/2017/RRMar18/","Data/2018/"};
    constexpr const char* dtpath = dtpath_.at(yid);

    const array<map<string,vector<const char*>>,yrs> dtfiles_ = {{
      {
        {"RunB" ,{"B_ZB.root", "B.root"}},
        {"RunC" ,{"C_ZB.root", "C.root"}},
        {"RunD" ,{"D_ZB.root", "D.root"}},
        {"RunE" ,{"E_ZB.root", "E.root"}},
        {"RunFe",{"Fe_ZB.root", "Fe.root"}},
        {"RunFl",{"Fl_ZB.root", "Fl.root"}},
        {"RunG" ,{"G_ZB.root", "G.root"}},
        {"RunH" ,{"H_ZB.root", "H.root"}}
      },
      {
        {"RunB",{"B_ZB.root", "B.root"}},
        {"RunC",{"C_ZB.root", "C.root"}},
        {"RunD",{"D_ZB.root", "D.root"}},
        {"RunE",{"E_ZB.root", "E.root"}},
        {"RunF",{"F_ZB.root", "F.root"}}
      },
      {
        {"RunH_FSQJ2",{"H_FSQJ2.root"}},
        {"RunH_FSQJ2Fwd",{"H_FSQJ2.root"}},
        {"RunH_LEG",{"H_LEG.root"}},
        {"RunH_LEGFwd",{"H_LEG.root"}},
        {"RunH_HEG",{"H_HEG.root"}},
        {"RunH_HEGFwd",{"H_HEG.root"}},
        {"RunH_ZB",{"H_ZB.root"}}
      },
      {
        {"RunA",{"A_ZB.root", "A.root"}},
        {"RunB",{"B_ZB.root", "B.root"}},
        {"RunC",{"C3_ZB.root","C3.root"}},
        {"RunD",{"D_ZB.root","D.root"}}
      }
    }};
    const map<string,vector<const char*>> dtfiles = dtfiles_.at(yid);
    //}

    //{ BEGIN MC: Generic options
    const array<map<string,vector<const char*>>,yrs> mcfiles_ = {{
      {
        {"P8M1",{"MC/2016/P8M1/FlatPthat_15to7000.root"}},
        {"HS1",{"MC/2016/HS1/FlatPthat_15to7000.root"}},
        {"NuGun",{"MC/2016/NuGun.root"}}
      },
      {
        {"P8M1",{"/2017/MC/P8M1/FlatPthat_15to7000.root"}},
        {"P8CP5",{"/2017/MC/P8CP5/FlatPthat_15to7000.root"}},
        {"HS1",{"/2017/MC/HS1/FlatPthat_15to7000.root"}},
        {"NuGun",{"/2017/MC/NuGun.root"}}
      },
      {
        {"P8M1",{"MC/2017/P8M1/FlatPthat_15to7000.root"}},
        {"P8CP5",{"MC/2017/P8CP5/FlatPthat_15to7000.root"}},
        {"HS1",{"MC/2017/HS1/FlatPthat_15to7000.root"}},
        {"NuGun",{"MC/2017/NuGun.root"}}
      },
      {
        {"P8CP5",{"MC/2018/P8CP5/FlatPthat_15to7000.root"}},
        {"HS1",{"MC/2017/HS1/FlatPthat_15to7000.root"}},
        {"NuGun",{"MC/2018/NuGun.root"}}
      }
    }};
    const map<string,vector<const char*>> mcfiles = mcfiles_.at(yid);
    //}

    //{ BEGIN MC: Process pThatbinned file options
    // All the following values need to be updated, if other source tuples are used.
    const array<const char*,yrs> pthatpath_ = {
      "MC/2016/P8M1/",
      "MC/2017/P8CP5/",
      "MC/2017/P8CP5/",
      "MC/2018/P8CP5/"
    };
    const char* pthatpath = pthatpath_.at(yid);
    // The corresponding ranges, the last number is ~inf
    const vector<double> pthatranges = {15,30,50,80,120,170,300,470,600,800,1000,1400,1800,2400,3200,20000};
    // Number of pthat bins
    const unsigned int npthatbins = pthatranges.size()-1;
    // The corresponding lumis in picobarns (current values for CUETP8M1). These need to be fetched from McM
    const vector<double> pthatsigmas =
      {1837410000,140932000,19204300,2762530,471100,117276,7823,648.2,186.9,32.293,9.4183,0.84265,0.114943,0.00682981,0.000165445};
    // These can be obtained using GetSliceEvts.C: the 3200toInf number of events
    const array<double,yrs> pthatnormalevts_ = {{
      391735,
      609460,
      609460,
      609460
    }};
    const double pthatnormalevts = pthatnormalevts_.at(yid);

    // The filenames need to be given here and in mk_HistosFill, since ROOT is exceedingly stupid
    const vector<const char*> pthatfiles = {
      "Pthat_15to30","Pthat_30to50","Pthat_50to80","Pthat_80to120","Pthat_120to170","Pthat_170to300",
      "Pthat_300to470","Pthat_470to600","Pthat_600to800","Pthat_800to1000","Pthat_1000to1400",
      "Pthat_1400to1800","Pthat_1800to2400","Pthat_2400to3200","Pthat_3200toInf"
    };
    //} END pthatbins stuff

  //} END DT/MC: File names

  //{ BEGIN RUN2 params
  constexpr double sqrts = 13000.; // GeV
  constexpr double emax = sqrts/2.; // Max possible jet pt
  constexpr double recopt = 15; // Min observed jet pt
  constexpr double xsecMinBias = 7.126E+10;
  constexpr double lumi = -4; // Unprescaled luminosity for plots in /fb
  //} END Run2

  //{ BEGIN Special HistosFill analyses that are not typically needed
  // Eta phi exclusion due to hot ECAL regions (produced with dataequality.C)
  constexpr bool doVetoHot = false;
  const constexpr char HotType[] = ""; // h2hotr (Robert) or h2hotm (Mikko)

  // Check for duplicates (warning: takes a lot of memory!)
  constexpr bool checkduplicates = false;
  //} END Special analyses that are not typically needed

  //{ BEGIN HistosNormalize (leave these off if not interested on details)
  // Correct for trigger efficiency based on MC
  constexpr bool dotrigeff = false; // CAUTION: Requires output-MC-1.root file
  // Correct pT<114 GeV only, if above dotrigeff=true
  constexpr bool dotrigefflowptonly = false; // CAUTION: Not needed
  // Correct for time-dependence (prescales) in data
  constexpr bool dotimedep = false; // CAUTION: Unknown consequences
  //} END HistosNormalize

  //{ BEGIN drawSummary
  // Center uncertainties around ansatz (true) or data (false)
  constexpr bool centerOnAnsatz = false;
  constexpr bool centerOnTheory = false;
  // Plot Pythia for final PRL results
  constexpr bool plotPythia = false;
  // Draw againts HERAPDF1.7 instead of PDF4LHC (drawSummary)
  constexpr bool herapdf = false;
  // Produce plots (also drawRunHistos)
  constexpr bool pdf = true;
  //} END drawSummary

  //{ BEGIN limits for HistosNormalize, dagostini, drawSummary, drawRunHistos
  // Minimum and maximum pT range to be plotted and fitted
  constexpr double fitptmin = 114;//43;
  // Changed on 2013-05-020: analysis from 49 GeV to 56 GeV
  constexpr double xmin57 = 114;//56;
  constexpr double xminpas = 114;//56;
  constexpr double xmin = 114;//24.;//20.;
  constexpr double xmax = 1497;//TEMP PATCH for partial data //1999.;
  //} END limits

  //{ BEGIN Binnings
  // Binning agreed within JTF: pT>100 GeV from CaloJet resolutions,
  // pT<100 GeV to optimize bin widths for PFJets and b-tagging
  // (little higher than resolution, but fairly flat relative width)
  // http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/CMSSW/QCDAnalysis/HighPtJetAnalysis/interface/DefaultPtBins.h?revision=1.2&view=markup
  // Logic: 'n' means number of bins (len-1) and 'no' the length of an array (len)
  constexpr const double ptrange[] = {
    1, 5, 6, 8, 10, 12, 15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832, 4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000
  };
  constexpr const unsigned int npts = sizeof(ptrange)/sizeof(ptrange[0])-1;

  // A wide binning for pt: these should agree with trigger turn-on places (typically 15 GeV is where we cut everything)
  constexpr const double wptrange[] = {
    1, 15, 21, 28, 37, 49, 64, 84, 114, 153, 196, 272, 330, 395, 468, 548, 686, 846, 1032, 1248, 1588, 2000, 2500, 3103, 3832, 4713, 5777, 7000
  };
  constexpr const int nwpts = sizeof(wptrange)/sizeof(wptrange[0])-1;

  // A very wide binning for pt: these should agree with trigger turn-on places (typically 15 GeV is where we cut everything)
  constexpr const double wwptrange[] = {
    15, 28, 40, 49, 64, 84, 114, 196, 272, 330, 395, 440, 468, 486, 507, 527, 548, 575, 618, 686, 905, 2116, 7000
  };
  constexpr const int nwwpts = sizeof(wwptrange)/sizeof(wwptrange[0])-1;

  // Optimized binning created by optimizeBins.C ("MC"; lumi 1000/pb, eff 1e+10%)
  // Using NLOxNP theory fit as input when available
  constexpr const unsigned int nopts_eta = 65;
  constexpr const double ptrangevseta[][nopts_eta] = {
    {10, 12, 15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3832, 6076, 6389}, // Eta_0.0-0.5
    {10, 12, 15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3637, 5220, 5492}, // Eta_0.5-1.0
    {10, 12, 15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2941, 3832}, // Eta_1.0-1.5
    {10, 12, 15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2500, 2640}, // Eta_1.5-2.0
    {10, 12, 15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684}, // Eta_2.0-2.5
    {10, 12, 15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032}, // Eta_2.5-3.0
    {10, 12, 15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032}, // Eta_3.0-3.5
    {10, 12, 15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032} // Eta_3.5-4.0
  };
  constexpr const unsigned int noptranges = sizeof(ptrangevseta)/sizeof(ptrangevseta[0]);

  constexpr const double wetarange[] = {
    -5.191, -3.839, -3.489, -3.139, -2.964, -2.853, -2.650, -2.500, -2.322, -2.172, -1.930, -1.653, -1.479, -1.305, -1.044, -0.783, -0.522, -0.261,
      0.000,  0.261,  0.522,  0.783,  1.044,  1.305,  1.479,  1.653,  1.930, 2.172,  2.322,  2.500,  2.650,  2.853,  2.964,  3.139,  3.489,  3.839, 5.191
  };
  constexpr const unsigned int nwetas = sizeof(wetarange)/sizeof(wetarange[0])-1;

  constexpr const double posetarange[] = {
    0, 0.261, 0.522, 0.783, 0.957, 1.131, 1.305, 1.479, 1.93, 2.322, 2.411, 2.5, 2.853, 2.964, 5.191
  };
  constexpr const unsigned int nposetas = sizeof(posetarange)/sizeof(posetarange[0])-1;

  // This agrees with the L2Relative eta grid
  constexpr const double etarange[] = {
    -5.191,-4.889,-4.716,-4.538,-4.363,-4.191,-4.013,-3.839,-3.664,-3.489,-3.314,-3.139,-2.964,-2.853,-2.65,-2.5,-2.322,-2.172,-2.043,-1.93,-1.83,-1.74,-1.653,-1.566,-1.479,-1.392,-1.305,-1.218,-1.131,-1.044,-0.957,-0.879,-0.783,-0.696,-0.609,-0.522,-0.435,-0.348,-0.261,-0.174,-0.087,
     0.000, 0.087, 0.174, 0.261,0.348, 0.435, 0.522, 0.609, 0.696, 0.783, 0.879, 0.957, 1.044, 1.131, 1.218,1.305, 1.392, 1.479, 1.566, 1.653, 1.74, 1.83, 1.93, 2.043, 2.172, 2.322, 2.5,2.65, 2.853, 2.964, 3.139, 3.314, 3.489, 3.664, 3.839, 4.013, 4.191, 4.363,4.538, 4.716, 4.889, 5.191
  };
  constexpr const unsigned int netas = sizeof(etarange)/sizeof(etarange[0])-1;

  constexpr const double ptrange_semi[] = {
    15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3832, 6076, 6389
  };
  constexpr const unsigned int npts_semi = sizeof(ptrange_semi)/sizeof(ptrange_semi[0])-1;

  // This agrees with the L2Relative pt grids
  constexpr const unsigned int nopts_etarange = 30;
  constexpr const double ptforetarange[][nopts_etarange] = {
    {0.001,8.18905,9.56088,11.3415,13.2548,15.3228,17.4045,20.9332,25.1423,6500}, // Eta -5.191 - -4.889
    {0.001,8.09693,8.46291,9.47773,10.8611,12.4063,14.7764,16.5554,19.0321,22.1756,26.3406,6500}, // Eta -4.889 - -4.716
    {0.001,8.62175,9.28651,9.92509,11.0462,12.6239,14.8162,17.2724,20.0703,23.0744,27.022,31.582,37.0425,6500}, // Eta -4.716 - -4.538
    {0.001,8.19106,9.08287,9.71782,10.3089,11.3204,12.3958,14.3076,16.8691,19.6909,22.8501,25.827,30.8363,34.9961,41.8463, 53.5881,6500}, // Eta -4.538 - -4.363
    {0.001,8.7089, 9.38133,10.2108,11.0151,11.9591,13.1765,15.192, 17.745, 20.6706,23.9236,27.4388,32.109,36.6285,44.0704, 56.5204,71.9924,6500}, // Eta -4.363 - -4.191
    {0.001,8.17008,8.90618,9.81619,10.5333,11.3527,12.3824,13.5726,15.5038,18.1614,21.2292,24.5013,28.0876,32.8164,37.3785,44.7306,57.3559,74.5293,93.7461,6500}, // Eta -4.191 - -4.013
    {0.001,8.30345, 8.9961,9.79351,10.671, 11.4433,12.1864,13.5411,15.5884,18.067, 21.3571,24.5688,28.2336,33.2231,37.4792,45.2691,58.2161,73.6572,95.5524,6500}, // Eta -4.013 - -3.839
    {0.001,8.16558,9.11333,9.72733,10.4778,11.4423,12.1853, 13.252,15.3462,17.9269,20.9427,24.3299,27.8204,32.3012,37.6055,45.1844,58.2032,74.9447, 96.893,128.846,6500}, // Eta -3.839 - -3.664
    {0.001,8.11512,8.73639,9.54122,10.2296,10.9595,11.9334,13.0218,14.9782,17.3737,20.1178,23.4363, 26.844,31.4635,36.1512,43.1385,56.1202,72.2718,93.4751,125.289,159.066,6500}, // Eta -3.664 - -3.489
    {0.001,8.46019,9.26473,9.85459,10.8225,11.4165,12.5846,14.5572,16.8992,19.6121,22.7387,26.0789, 30.616,35.5618,42.7386,55.7794, 71.665,93.5751,125.095,161.693,6500}, // Eta -3.489 - -3.314
    {0.001,8.23805,8.71197,9.55156,10.3231,10.8811,11.9536,13.7771,16.0642,18.6649,21.7545,24.8346, 29.437,34.1676,41.5739,54.3849, 71.401,94.2187,126.648,163.925,226.035,6500}, // Eta -3.314 - -3.139
    {0.001,8.16034,8.81596,9.69316,10.2368,12.0442,13.925, 16.2753,18.5528,21.4285,25.3147,29.6247,35.7128,47.2466,61.8202,81.7318, 110.93,144.732,200.631,6500}, // Eta -3.139 - -2.964
    {0.001,8.26166,8.90167,9.49292,11.0085,12.9351,15.0825,17.3825,20.0333,24.2595,28.0717,33.8683,44.9766,58.1777,76.7748, 102.11,133.426,184.699,6500}, // Eta -2.964 - -2.853
    {0.001,8.36371,8.92198,9.77153,11.315, 13.1631,15.7907,18.4428,21.5671,25.9998,30.7934,37.7427,50.0599,65.1484,85.5094, 113.76,147.857,205.162,304.612,409.367,6500}, // Eta -2.853 - -2.65
    {0.001,8.47032,8.88584,9.51497,10.5274,12.1281,14.1925,16.8318,19.6988,23.0446,27.1608,32.3327,40.0249,52.6461,68.4426,88.8971,117.483, 152.54,211.262,311.456,418.792,6500}, // Eta -2.65 - -2.5
    {0.001,8.40133,8.99775,9.74601,10.5462,11.4197,13.1177,15.6528,18.5658,21.7104,25.0901,30.0538,34.6661,42.2751,54.8591,70.7345, 91.376,119.643,153.512,212.265, 312.58,419.902,573.025,6500}, // Eta -2.5 - -2.322
    {0.001,8.74798,9.24239,10.2552,10.8819,12.0464,13.9516,16.2922,19.2373,22.4772,25.8892,31.0136,35.8871,43.2407,55.8034,71.2558,91.3832,119.786, 153.52,210.676,308.577,414.835,564.805,761.975,6500}, // Eta -2.322 - -2.172
    {0.001,8.04197,8.72199,9.44128,10.2729,10.7686,12.2256,13.9299,16.6705, 19.718,22.8986,26.5793, 31.485, 36.598,43.5741,56.2608,71.5749,  91.52,120.297,152.732,211.327,307.741, 415.75,569.502,771.067,6500}, // Eta -2.172 - -2.043
    {0.001,8.10277,8.72915,9.45719,10.2363,10.7904, 12.129,14.0745,16.8145,19.6942,23.0861,26.8287,31.7178,36.3868,44.1165,56.4471,71.6123,  91.92,120.316,153.649,211.349,308.061,417.302,572.968,774.259,6500}, // Eta -2.043 - -1.93
    {0.001,8.20075,8.71903,9.54345,10.2806,11.0698,12.2317,14.2846,16.9467,19.8605,23.3896,26.7771,31.8045,36.5707,44.1153,56.4483,71.8051,91.7415,120.128,153.677,212.119,310.021,419.574,  576.2,778.739,6500}, // Eta -1.93 - -1.83
    {0.001,8.29482,8.88945,9.64961, 10.468,11.1091,12.4607,14.4201,16.9741,20.1338,23.3485,27.2456,31.9383,36.8104,44.3701,56.9459,71.8148,92.9389,121.047,155.226,213.695,311.814,420.762,578.298,784.979,1046.33,6500}, // Eta -1.83 - -1.74
    {0.001,8.18393,8.94778,9.68401,10.4444, 11.521,12.4713,14.5348,17.5081,20.4818,23.7056,27.7277,32.1962,37.3623,44.8854,57.6251,73.4187,94.2007,123.132, 156.95,216.239,312.932,422.059,579.382,786.062,1051.87,6500}, // Eta -1.74 - -1.653
    {0.001,8.46923,9.17215,9.92386,10.7135,11.4205,12.6764,14.7851, 17.315,20.5832,24.0113,27.7256,33.1026,37.7015,45.3001,57.9412,73.8795,94.5391,123.858,157.518,216.581,313.752,421.215,578.695,786.406,1055.49,6500}, // Eta -1.653 - -1.566
    {0.001,8.43826,9.03479,10.1668,10.6612,11.3562,12.7936,14.6687,17.5417,20.6737,24.1911,27.8625,32.6482,37.2586,44.7732,57.2521,72.4937,92.4663,120.371,154.172,211.083,306.864, 414.25,568.336,774.784,1045.07,6500}, // Eta -1.566 - -1.479
    {0.001,8.16683,8.95343,9.71527,10.3993,11.4551,12.5125, 14.713,17.1524, 20.573,23.9643,27.5667,32.4425,37.2575,44.7116,56.9987, 71.658,91.6285,118.628, 150.82,206.604,296.477,397.585,541.594,732.131,985.803,6500}, // Eta -1.479 - -1.392
    {0.001,8.29806,8.96471,9.80488,10.5008,11.1208,12.4005,14.4694,17.1356,20.2397,23.5452,27.4912, 32.662,37.2028,44.5064,56.9274,71.8626,91.7305,119.578,151.773,208.015,301.083,404.234,552.173,748.599,1012.26,1469.42,1914.86,6500}, // Eta -1.392 - -1.305
    {0.001, 8.2742,8.95622,9.77446,10.4675,11.2753,12.6025,14.5793,17.1944,20.4839,23.8802,27.8941,32.7702,37.3783,44.6355, 56.935,71.6817,91.5832, 119.21,151.391,208.183,300.362,403.583,550.244,748.531, 1013.1,1476.52,1932.68,6500}, // Eta -1.305 - -1.218
    {0.001,8.39023,9.07571, 9.8498,10.6137,11.3635,12.6893,14.7606,17.3359, 20.745,24.3035,27.9426,32.9679,37.9407,45.2531,57.5954,72.8853,93.1481, 120.37,153.263,209.345,303.937,407.723,556.441,755.469,1027.33,1493.64,1960.82,6500}, // Eta -1.218 - -1.131
    {0.001,8.40776,9.44644,9.96012,10.8493,11.7382,12.7967,15.0248,17.7285, 21.088,24.5022,28.3469,  33.38,38.2749,45.7334, 58.639,73.5993, 94.119,122.284,155.907,212.803,307.778, 413.17,565.933,766.141,1041.45,1520.22,1992.78,6500}, // Eta -1.131 - -1.044
    {0.001,8.53272,9.23816,10.1245,10.9498,11.4397,12.8282,15.0759,18.0622,21.2586,24.7361,28.7808,33.5719,38.7384,46.1578,58.8517, 74.301,94.8275,123.108,156.894,215.682,311.212,416.907,569.849,772.406,1047.27,1535.82,2006.57,2474.45,6500}, // Eta -1.044 - -0.957
    {0.001,8.54225,9.29918,10.1587,10.7852,11.6982,12.8739,15.3032,17.9744,21.4435,24.6629,28.6957,34.0125,38.9531,46.6211,59.2665,74.6405, 95.466,123.845,157.544,216.497,311.846,416.725,568.435,771.039,1051.04,1531.03,2003.89,2479.62,6500}, // Eta -0.957 - -0.879
    {0.001,8.47911,9.27852,9.96655,10.7706,11.8369,13.1844,15.3448, 18.056,21.3606,24.8457,29.0507,34.0799,39.0173,47.0277,59.5866,75.0673,95.7578,124.421,158.302,216.987,  312.8,419.064,572.711,775.423,1053.51, 1540.1,2020.28,2495.27,6500}, // Eta -0.879 - -0.783
    {0.001,8.45038,9.36796,10.2143,10.8706,11.8925, 13.011,15.2977,18.1884,21.6443,25.1326,29.2057, 34.411,39.3334,46.9529,59.5791,75.5097,95.9778,124.886,159.259, 218.38,314.197,419.979,576.673,779.157,1062.13,1549.56,2029.68,2509.82,6500}, // Eta -0.783 - -0.696
    {0.001,8.51946,9.28417,10.0471,10.9678,11.8894,13.0347,15.2009,18.2503,21.5656,25.2813,29.1852,34.2698,39.4476,46.9851,60.0589,75.5744, 96.427,125.623,160.485,220.021,316.777,424.148,580.363,786.685,1068.81,1566.82,2051.36,2532.57,6500}, // Eta -0.696 - -0.609
    {0.001,8.59497,9.43456,10.2091,11.0292,11.8715,13.1409,15.3479,18.1431,21.6066,25.1134,29.0979,34.2564,39.4264,47.2096,59.9178,75.6962,96.9782,125.844,160.004,219.581, 316.93,424.498,580.838,785.388,1070.99,1564.54,2053.93,2536.59,6500}, // Eta -0.609 - -0.522
    {0.001,8.53287,9.33337,9.98434,10.8731,11.8056,13.0628,15.2387,18.1692,21.5006,25.2612,29.2195,34.4581,39.1737,46.8605,59.9906,75.5894,96.2318,125.572,159.346,219.117, 316.17,423.444,578.987,782.451,1071.36,1563.27,2045.88,2528.94,6500}, // Eta -0.522 - -0.435
    {0.001,8.57838,9.38883,10.1843,10.8827,11.9154,12.9941,15.3042,18.1795,21.6449,25.2651,29.0985,34.3197,39.2961,47.0243,60.1639,75.2877, 96.594,125.592,160.019,220.162,317.265,426.279, 582.34,788.662,1074.93,1572.37,2061.27,2548.42,6500}, // Eta -0.435 - -0.348
    {0.001,8.51542,9.30176,10.1989,10.9377,11.8034,13.1019, 15.267,18.0902,21.5794,24.9491,29.0819,34.3709,39.6481,47.0879,59.6539,75.3709,96.6945,125.926,160.273,220.032,317.528,425.129,582.411,787.573,1076.53,1571.69,2058.15,2540.56,6500}, // Eta -0.348 - -0.261
    {0.001, 8.6185,9.30878,10.1582,10.9375,11.8703, 13.116,15.3391,18.1093,21.5422,25.2252,29.0661,34.0226, 39.413,46.8834,60.0412,75.4099,96.3454,125.683,160.196,219.732,317.587,425.256,581.658,787.252,1076.84,1573.64,2061.39,2549.05,6500}, // Eta -0.261 - -0.174
    {0.001,8.53946,9.32627,10.1424,10.9927,11.6111,13.1235,15.3157,18.2096,21.6905,25.1096,  29.23,34.3973, 39.475,47.1265,60.0217,75.4015, 96.348,125.407,159.888,219.702,317.427,425.878,582.118,787.759,1075.74,1573.94,2062.59,2542.44,6500}, // Eta -0.174 - -0.087
    {0.001,8.55767, 9.3614, 10.059,10.8127,11.7001,12.9095,15.3406,18.0812,21.6098,25.2671,29.2199,34.0778,39.5407,47.1427,59.8302,75.3168,96.4767,125.088,160.195,219.785,317.565,426.405,584.132,789.825,1078.47,1577.67,2067.76,2553.99,6500}, // Eta -0.087 - 0
    {0.001,8.55767, 9.3614, 10.059,10.8127,11.7001,12.9095,15.3406,18.0812,21.6098,25.2671,29.2199,34.0778,39.5407,47.1427,59.8302,75.3168,96.4767,125.088,160.195,219.785,317.565,426.405,584.132,789.825,1078.47,1577.67,2067.76,2553.99,6500}, // Eta 0 - 0.087
    {0.001,8.53946,9.32627,10.1424,10.9927,11.6111,13.1235,15.3157,18.2096,21.6905,25.1096,  29.23,34.3973, 39.475,47.1265,60.0217,75.4015, 96.348,125.407,159.888,219.702,317.427,425.878,582.118,787.759,1075.74,1573.94,2062.59,2542.44,6500}, // Eta 0.087 - 0.174
    {0.001, 8.6185,9.30878,10.1582,10.9375,11.8703, 13.116,15.3391,18.1093,21.5422,25.2252,29.0661,34.0226, 39.413,46.8834,60.0412,75.4099,96.3454,125.683,160.196,219.732,317.587,425.256,581.658,787.252,1076.84,1573.64,2061.39,2549.05,6500}, // Eta 0.174 - 0.261
    {0.001,8.51542,9.30176,10.1989,10.9377,11.8034,13.1019, 15.267,18.0902,21.5794,24.9491,29.0819,34.3709,39.6481,47.0879,59.6539,75.3709,96.6945,125.926,160.273,220.032,317.528,425.129,582.411,787.573,1076.53,1571.69,2058.15,2540.56,6500}, // Eta 0.261 - 0.348
    {0.001,8.57838,9.38883,10.1843,10.8827,11.9154,12.9941,15.3042,18.1795,21.6449,25.2651,29.0985,34.3197,39.2961,47.0243,60.1639,75.2877, 96.594,125.592,160.019,220.162,317.265,426.279, 582.34,788.662,1074.93,1572.37,2061.27,2548.42,6500}, // Eta 0.348 - 0.435
    {0.001,8.53287,9.33337,9.98434,10.8731,11.8056,13.0628,15.2387,18.1692,21.5006,25.2612,29.2195,34.4581,39.1737,46.8605,59.9906,75.5894,96.2318,125.572,159.346,219.117, 316.17,423.444,578.987,782.451,1071.36,1563.27,2045.88,2528.94,6500}, // Eta 0.435 - 0.522
    {0.001,8.59497,9.43456,10.2091,11.0292,11.8715,13.1409,15.3479,18.1431,21.6066,25.1134,29.0979,34.2564,39.4264,47.2096,59.9178,75.6962,96.9782,125.844,160.004,219.581, 316.93,424.498,580.838,785.388,1070.99,1564.54,2053.93,2536.59,6500}, // Eta 0.522 - 0.609
    {0.001,8.51946,9.28417,10.0471,10.9678,11.8894,13.0347,15.2009,18.2503,21.5656,25.2813,29.1852,34.2698,39.4476,46.9851,60.0589,75.5744, 96.427,125.623,160.485,220.021,316.777,424.148,580.363,786.685,1068.81,1566.82,2051.36,2532.57,6500}, // Eta 0.609 - 0.696
    {0.001,8.45038,9.36796,10.2143,10.8706,11.8925, 13.011,15.2977,18.1884,21.6443,25.1326,29.2057, 34.411,39.3334,46.9529,59.5791,75.5097,95.9778,124.886,159.259, 218.38,314.197,419.979,576.673,779.157,1062.13,1549.56,2029.68,2509.82,6500}, // Eta 0.696 - 0.783
    {0.001,8.47911,9.27852,9.96655,10.7706,11.8369,13.1844,15.3448, 18.056,21.3606,24.8457,29.0507,34.0799,39.0173,47.0277,59.5866,75.0673,95.7578,124.421,158.302,216.987,  312.8,419.064,572.711,775.423,1053.51, 1540.1,2020.28,2495.27,6500}, // Eta 0.783 - 0.879
    {0.001,8.54225,9.29918,10.1587,10.7852,11.6982,12.8739,15.3032,17.9744,21.4435,24.6629,28.6957,34.0125,38.9531,46.6211,59.2665,74.6405, 95.466,123.845,157.544,216.497,311.846,416.725,568.435,771.039,1051.04,1531.03,2003.89,2479.62,6500}, // Eta 0.879 - 0.957
    {0.001,8.53272,9.23816,10.1245,10.9498,11.4397,12.8282,15.0759,18.0622,21.2586,24.7361,28.7808,33.5719,38.7384,46.1578,58.8517, 74.301,94.8275,123.108,156.894,215.682,311.212,416.907,569.849,772.406,1047.27,1535.82,2006.57,2474.45,6500}, // Eta 0.957 - 1.044
    {0.001,8.40776,9.44644,9.96012,10.8493,11.7382,12.7967,15.0248,17.7285, 21.088,24.5022,28.3469,  33.38,38.2749,45.7334, 58.639,73.5993, 94.119,122.284,155.907,212.803,307.778, 413.17,565.933,766.141,1041.45,1520.22,1992.78,6500}, // Eta 1.044 - 1.131
    {0.001,8.39023,9.07571, 9.8498,10.6137,11.3635,12.6893,14.7606,17.3359, 20.745,24.3035,27.9426,32.9679,37.9407,45.2531,57.5954,72.8853,93.1481, 120.37,153.263,209.345,303.937,407.723,556.441,755.469,1027.33,1493.64,1960.82,6500}, // Eta 1.131 - 1.218
    {0.001, 8.2742,8.95622,9.77446,10.4675,11.2753,12.6025,14.5793,17.1944,20.4839,23.8802,27.8941,32.7702,37.3783,44.6355, 56.935,71.6817,91.5832, 119.21,151.391,208.183,300.362,403.583,550.244,748.531, 1013.1,1476.52,1932.68,6500}, // Eta 1.218 - 1.305
    {0.001,8.29806,8.96471,9.80488,10.5008,11.1208,12.4005,14.4694,17.1356,20.2397,23.5452,27.4912, 32.662,37.2028,44.5064,56.9274,71.8626,91.7305,119.578,151.773,208.015,301.083,404.234,552.173,748.599,1012.26,1469.42,1914.86,6500}, // Eta 1.305 - 1.392
    {0.001,8.16683,8.95343,9.71527,10.3993,11.4551,12.5125, 14.713,17.1524, 20.573,23.9643,27.5667,32.4425,37.2575,44.7116,56.9987, 71.658,91.6285,118.628, 150.82,206.604,296.477,397.585,541.594,732.131,985.803,6500}, // Eta 1.392 - 1.479
    {0.001,8.43826,9.03479,10.1668,10.6612,11.3562,12.7936,14.6687,17.5417,20.6737,24.1911,27.8625,32.6482,37.2586,44.7732,57.2521,72.4937,92.4663,120.371,154.172,211.083,306.864, 414.25,568.336,774.784,1045.07,6500}, // Eta 1.479 - 1.566
    {0.001,8.46923,9.17215,9.92386,10.7135,11.4205,12.6764,14.7851, 17.315,20.5832,24.0113,27.7256,33.1026,37.7015,45.3001,57.9412,73.8795,94.5391,123.858,157.518,216.581,313.752,421.215,578.695,786.406,1055.49,6500}, // Eta 1.566 - 1.653
    {0.001,8.18393,8.94778,9.68401,10.4444, 11.521,12.4713,14.5348,17.5081,20.4818,23.7056,27.7277,32.1962,37.3623,44.8854,57.6251,73.4187,94.2007,123.132, 156.95,216.239,312.932,422.059,579.382,786.062,1051.87,6500}, // Eta 1.653 - 1.74
    {0.001,8.29482,8.88945,9.64961, 10.468,11.1091,12.4607,14.4201,16.9741,20.1338,23.3485,27.2456,31.9383,36.8104,44.3701,56.9459,71.8148,92.9389,121.047,155.226,213.695,311.814,420.762,578.298,784.979,1046.33,6500}, // Eta 1.74  - 1.83
    {0.001,8.20075,8.71903,9.54345,10.2806,11.0698,12.2317,14.2846,16.9467,19.8605,23.3896,26.7771,31.8045,36.5707,44.1153,56.4483,71.8051,91.7415,120.128,153.677,212.119,310.021,419.574,  576.2,778.739,6500}, // Eta 1.83 - 1.93
    {0.001,8.10277,8.72915,9.45719,10.2363,10.7904, 12.129,14.0745,16.8145,19.6942,23.0861,26.8287,31.7178,36.3868,44.1165,56.4471,71.6123,  91.92,120.316,153.649,211.349,308.061,417.302,572.968,774.259,6500}, // Eta 1.93 - 2.043
    {0.001,8.04197,8.72199,9.44128,10.2729,10.7686,12.2256,13.9299,16.6705, 19.718,22.8986,26.5793, 31.485, 36.598,43.5741,56.2608,71.5749,  91.52,120.297,152.732,211.327,307.741, 415.75,569.502,771.067,6500}, // Eta 2.043 - 2.172
    {0.001,8.74798,9.24239,10.2552,10.8819,12.0464,13.9516,16.2922,19.2373,22.4772,25.8892,31.0136,35.8871,43.2407,55.8034,71.2558,91.3832,119.786, 153.52,210.676,308.577,414.835,564.805,761.975,6500}, // Eta 2.172 - 2.322
    {0.001,8.40133,8.99775,9.74601,10.5462,11.4197,13.1177,15.6528,18.5658,21.7104,25.0901,30.0538,34.6661,42.2751,54.8591,70.7345, 91.376,119.643,153.512,212.265, 312.58,419.902,573.025,6500}, // Eta 2.322 - 2.5
    {0.001,8.47032,8.88584,9.51497,10.5274,12.1281,14.1925,16.8318,19.6988,23.0446,27.1608,32.3327,40.0249,52.6461,68.4426,88.8971,117.483, 152.54,211.262,311.456,418.792,6500}, // Eta 2.5 - 2.65
    {0.001,8.36371,8.92198,9.77153,11.315, 13.1631,15.7907,18.4428,21.5671,25.9998,30.7934,37.7427,50.0599,65.1484,85.5094, 113.76,147.857,205.162,304.612,409.367,6500}, // Eta 2.65 - 2.853
    {0.001,8.26166,8.90167,9.49292,11.0085,12.9351,15.0825,17.3825,20.0333,24.2595,28.0717,33.8683,44.9766,58.1777,76.7748, 102.11,133.426,184.699,6500}, // Eta 2.853 - 2.964
    {0.001,8.16034,8.81596,9.69316,10.2368,12.0442,13.925, 16.2753,18.5528,21.4285,25.3147,29.6247,35.7128,47.2466,61.8202,81.7318, 110.93,144.732,200.631,6500}, // Eta 2.964 - 3.139
    {0.001,8.23805,8.71197,9.55156,10.3231,10.8811,11.9536,13.7771,16.0642,18.6649,21.7545,24.8346, 29.437,34.1676,41.5739,54.3849, 71.401,94.2187,126.648,163.925,226.035,6500}, // Eta 3.139 - 3.314
    {0.001,8.46019,9.26473,9.85459,10.8225,11.4165,12.5846,14.5572,16.8992,19.6121,22.7387,26.0789, 30.616,35.5618,42.7386,55.7794, 71.665,93.5751,125.095,161.693,6500}, // Eta 3.314 - 3.489
    {0.001,8.11512,8.73639,9.54122,10.2296,10.9595,11.9334,13.0218,14.9782,17.3737,20.1178,23.4363, 26.844,31.4635,36.1512,43.1385,56.1202,72.2718,93.4751,125.289,159.066,6500}, // Eta 3.489 - 3.664
    {0.001,8.16558,9.11333,9.72733,10.4778,11.4423,12.1853, 13.252,15.3462,17.9269,20.9427,24.3299,27.8204,32.3012,37.6055,45.1844,58.2032,74.9447, 96.893,128.846,6500}, // Eta 3.664 - 3.839
    {0.001,8.30345, 8.9961,9.79351,10.671, 11.4433,12.1864,13.5411,15.5884,18.067, 21.3571,24.5688,28.2336,33.2231,37.4792,45.2691,58.2161,73.6572,95.5524,6500}, // Eta 3.839 - 4.013
    {0.001,8.17008,8.90618,9.81619,10.5333,11.3527,12.3824,13.5726,15.5038,18.1614,21.2292,24.5013,28.0876,32.8164,37.3785,44.7306,57.3559,74.5293,93.7461,6500}, // Eta 4.013 - 4.191
    {0.001,8.7089, 9.38133,10.2108,11.0151,11.9591,13.1765,15.192, 17.745, 20.6706,23.9236,27.4388,32.109,36.6285,44.0704, 56.5204,71.9924,6500}, // Eta 4.191 - 4.363
    {0.001,8.19106,9.08287,9.71782,10.3089,11.3204,12.3958,14.3076,16.8691,19.6909,22.8501,25.827,30.8363,34.9961,41.8463, 53.5881,6500}, // Eta 4.363 - 4.538
    {0.001,8.62175,9.28651,9.92509,11.0462,12.6239,14.8162,17.2724,20.0703,23.0744,27.022,31.582,37.0425,6500}, // Eta 4.538 - 4.716
    {0.001,8.09693,8.46291,9.47773,10.8611,12.4063,14.7764,16.5554,19.0321,22.1756,26.3406,6500}, // Eta 4.716 - 4.889
    {0.001,8.18905,9.56088,11.3415,13.2548,15.3228,17.4045,20.9332,25.1423,6500}, // Eta 4.889 - 5.191
  };
  constexpr const int ptbins[] = {9,11,13,16,17,19,19,20,21,20,21,19,18,20,21,23,24,25,25,25,26,26,26,26,26,28,28,28,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,28,28,28,26,26,26,26,26,25,25,25,24,23,21,20,18,19,21,20,21,20,19,19,17,16,13,11,9};

  constexpr const double pvrange[] = {
    -0.5,0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5,12.5,13.5,14.5,15.5,16.5,17.5,18.5,19.5,20.5,21.5,22.5,23.5,24.5,25.5,26.5,27.5,28.5,29.5,30.5,31.5,32.5,33.5,34.5,35.5,36.5,37.5,38.5,39.5,40.5,41.5,42.5,43.5,44.5,45.5,46.5,47.5,48.5,49.5
  };
  constexpr const unsigned int npvs = sizeof(pvrange)/sizeof(pvrange[0])-1;

  constexpr const double phirange[] = {
    -3.15,-3.097959,-3.054326,-3.010693,-2.967060,-2.923426,-2.879793,-2.836160,-2.792527,-2.748894,-2.705260,-2.661627,-2.617994,-2.574361,-2.530727,-2.487094,-2.443461,-2.399828,-2.356194,-2.312561,-2.268928,-2.225295,-2.181662,-2.138028,-2.094395,-2.050762,-2.007129,-1.963495,-1.919862,-1.876229,-1.832596,-1.788962,-1.745329,-1.701696,-1.658063,-1.614430,-1.570796,-1.527163,-1.483530,-1.439897,-1.396263,-1.352630,-1.308997,-1.265364,-1.221730,-1.178097,-1.134464,-1.090831,-1.047198,-1.003564,-0.959931,-0.916298,-0.872665,-0.829031,-0.785398,-0.741765,-0.698132,-0.654498,-0.610865,-0.567232,-0.523599,-0.479966,-0.436332,-0.392699,-0.349066,-0.305433,-0.261799,-0.218166,-0.174533,-0.130900,-0.087266,-0.043633,0.000000,0.043633,0.087266,0.130900,0.174533,0.218166,0.261799,0.305433,0.349066,0.392699,0.436332,0.479966,0.523599,0.567232,0.610865,0.654498,0.698132,0.741765,0.785398,0.829031,0.872665,0.916298,0.959931,1.003564,1.047198,1.090831,1.134464,1.178097,1.221730,1.265364,1.308997,1.352630,1.396263,1.439897,1.483530,1.527163,1.570796,1.614430,1.658063,1.701696,1.745329,1.788962,1.832596,1.876229,1.919862,1.963495,2.007129,2.050762,2.094395,2.138028,2.181662,2.225295,2.268928,2.312561,2.356194,2.399828,2.443461,2.487094,2.530727,2.574361,2.617994,2.661627,2.705260,2.748894,2.792527,2.836160,2.879793,2.923426,2.967060,3.010693,3.054326,3.097959,3.15
  };
  constexpr const unsigned int nphis = sizeof(phirange)/sizeof(phirange[0])-1;

  constexpr const double posphirange[] = {
  0.000000,0.021817,0.043633,0.065450,0.087266,0.109083,0.130900,0.152716,0.174533,0.196350,0.218166,0.239983,0.261799,0.283616,0.305433,0.327249,0.349066,0.370882,0.392699,0.414516,0.436332,0.458149,0.479966,0.501782,0.523599,0.545415,0.567232,0.589049,0.610865,0.632682,0.654498,0.676315,0.698132,0.719948,0.741765,0.763582,0.785398,0.807215,0.829031,0.850848,0.872665,0.894481,0.916298,0.938114,0.959931,0.981748,1.003564,1.025381,1.047198,1.069014,1.090831,1.112647,1.134464,1.156281,1.178097,1.199914,1.221730,1.243547,1.265364,1.287180,1.308997,1.330814,1.352630,1.374447,1.396263,1.418080,1.439897,1.461713,1.483530,1.505346,1.527163,1.548980,1.570796,1.592613,1.614430,1.636246,1.658063,1.679879,1.701696,1.723513,1.745329,1.767146,1.788962,1.810779,1.832596,1.854412,1.876229,1.898046,1.919862,1.941679,1.963495,1.985312,2.007129,2.028945,2.050762,2.072578,2.094395,2.116212,2.138028,2.159845,2.181662,2.203478,2.225295,2.247111,2.268928,2.290745,2.312561,2.334378,2.356194,2.378011,2.399828,2.421644,2.443461,2.465278,2.487094,2.508911,2.530727,2.552544,2.574361,2.596177,2.617994,2.639810,2.661627,2.683444,2.705260,2.727077,2.748894,2.770710,2.792527,2.814343,2.836160,2.857977,2.879793,2.901610,2.923426,2.945243,2.967060,2.988876,3.010693,3.032510,3.054326,3.076143,3.097959,3.119776,3.15
  };
  constexpr const unsigned int nposphis = sizeof(posphirange)/sizeof(posphirange[0])-1;

  constexpr const double wphirange[] = {
    -3.15,-2.96706,-2.79253,-2.61799,-2.44346,-2.26893,-2.0944,-1.91986,-1.74533,-1.5708,-1.39626,-1.22173,-1.0472,-0.872665,-0.698132,-0.523599,-0.349066,-0.174533,0,0.174533,0.349066,0.523599,0.698132,0.872665,1.0472,1.22173,1.39626,1.5708,1.74533,1.91986,2.0944,2.26893,2.44346,2.61799,2.79253,2.96706,3.15
  };
  constexpr const unsigned int nwphis = sizeof(wphirange)/sizeof(wphirange[0])-1;

  constexpr const double wposphirange[] = {
    0,0.0872665,0.174533,0.261799,0.349066,0.436332,0.523599,0.610865,0.698132,0.785398,0.872665,0.959931,1.0472,1.13446,1.22173,1.309,1.39626,1.48353,1.5708,1.65806,1.74533,1.8326,1.91986,2.00713,2.0944,2.18166,2.26893,2.35619,2.44346,2.53073,2.61799,2.70526,2.79253,2.87979,2.96706,3.05433,3.15
  };
  constexpr const unsigned int nwposphis = sizeof(wposphirange)/sizeof(wposphirange[0])-1;

  //} END Binnings
}
#endif // STNGS
