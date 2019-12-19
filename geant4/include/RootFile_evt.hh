#ifndef RootFileRootFile_evt_h
#define RootFileRootFile_evt_h 1
class TH1D;
class TFile;
class TTree;
class RootFile_evt
{
public:
  RootFile_evt();
  ~RootFile_evt();

public:
  void Create();
  void EndOfAction();
  void FillTree();


  TTree* GetTree()  const {return tree;} 
  TFile* GetFileRoot() const {return hfile;}

  //------------------------TOT Energy by Material-------------------------

 G4double GettotEPb() const {return ftotEPb;}
  void SettotEPb(G4double val){ftotEPb=val;}

  G4double GetTime() const {return ftime;}
  void SetTime(G4double val){ftime=val;}

  

//event
  G4int GetEvent() const {return fevent;}
  void SetEvent(G4int val){fevent=val;}

private:

  TFile* hfile;
  TTree* tree;

  G4double ftotEPb;
  G4double ftime;

  G4int fevent;
  
};

#endif
