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


  //  TH1D* GethEdep0() const {return hEdep_0;} 
  // TH1D* GethEdep1() const {return hEdep_1;} 
  //TH1D* GethEKinelost0() const {return hEKinelost_0;} 
  //TH1D* GethEKinelost1() const {return hEKinelost_1;} 

  TTree* GetTree()  const {return tree;} 
  TFile* GetFileRoot() const {return hfile;}
 
 




  G4int GetgPb() const {return fgPb;}
  void SetgPb(G4int val){fgPb=val;}
  G4int GetnPb() const {return fnPb;}
  void SetnPb(G4int val){fnPb=val;}
  G4int GetePb() const {return fePb;}
  void SetePb(G4int val){fePb=val;}
  G4int GetmuPb() const {return fmuPb;}
  void SetmuPb(G4int val){fmuPb=val;}
   G4int GetotherPb() const {return fotherPb;}
   void SetotherPb(G4int val){fotherPb=val;}
 


 


  

  G4double GetEdep_gPb() const {return fEdep_gPb;}
  void SetEdep_gPb(G4double val){fEdep_gPb=val;}
  G4double GetEdep_nPb() const {return fEdep_nPb;}
  void SetEdep_nPb(G4double val){fEdep_nPb=val;}
  G4double GetEdep_ePb() const {return fEdep_ePb;}
  void SetEdep_ePb(G4double val){fEdep_ePb=val;}
  G4double GetEdep_muPb() const {return fEdep_muPb;}
  void SetEdep_muPb(G4double val){fEdep_muPb=val;}
  G4double GetEdep_otherPb() const {return fEdep_otherPb;}
  void SetEdep_otherPb(G4double val){fEdep_otherPb=val;}
 


  


  //------------------------TOT Energy by Material-------------------------

 G4double GettotEPb() const {return ftotEPb;}
  void SettotEPb(G4double val){ftotEPb=val;}

  


 
  
  G4double Getekin0() const {return fekin0;}
  void Setekin0(G4double val){fekin0=val;}
  G4double Getekin1() const {return fekin1;}
  void Setekin1(G4double val){fekin1=val;}

  G4double GetE0() const {return fE0;}
  void SetE0(G4double val){fE0=val;}
  G4double GetE1() const {return fE1;}
  void SetE1(G4double val){fE1=val;}
  G4double GetE2() const {return fE2;}
  void SetE2(G4double val){fE2=val;}
  G4double GetE3() const {return fE3;}
  void SetE3(G4double val){fE3=val;}
  

//event
  G4int GetEvent() const {return fevent;}
  void SetEvent(G4int val){fevent=val;}




 //deposite energy without particle created from other scint
  // G4double Getedeptot_woS1H0() const {return fedeptot_woS1H0;}
  // void Setedeptot_woS1H0(G4double val){fedeptot_woS1H0=val;}
  // G4double Getedeptot_woS0H1() const {return fedeptot_woS0H1;}
  // void Setedeptot_woS0H1(G4double val){fedeptot_woS0H1=val;}
  
 
  //deposite energy by particle created from other scint
  //  G4double GetedeptotSH0() const {return fedeptotSH0;}
  // void SetedeptotSH0(G4double val){fedeptotSH0=val;}
  // G4double GetedeptotSH1() const {return fedeptotSH1;}
  // void SetedeptotSH1(G4double val){fedeptotSH1=val;}

private:

  TFile* hfile;
  TTree* tree;

  G4int fgPb,fnPb,fePb,fotherPb,fmuPb;


  G4double fEdep_gPb,fEdep_nPb,fEdep_ePb,fEdep_otherPb,fEdep_muPb;
  G4double ftotEPb;


private: 
 
  
 
  G4double fekin0;
  G4double fekin1;
  G4double fE0;
  G4double fE1;
  G4double fE2;
  G4double fE3;
  G4int fevent;
  
};

#endif
