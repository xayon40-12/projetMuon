#include "electronics.hh"

std::vector<bool> gate(std::vector<double> &energy, double threshold, double gateTime, double binTime)
{
<<<<<<< HEAD

  std::vector<bool> result(energy.size();
=======
  std::vector<bool> result(energy.size());
>>>>>>> e70ed38e58cfbaa52e6211db21d313aaeb693e09
  for (int i=0;energy.size();i++)
    {
      if(energy[i]>threshold)
	{
	  for (int max=i+(gateTime/binTime);i<energy.size() && i<max;i++){result[i]=true;}
	}
      else{result[i]=false;}
    }

return result;
}




std::vector<bool> coincidence(std::vector<bool> &energy1,std::vector<bool> &energy2, double gateTime, double binTime)
  {
    std::vector<bool> result(energy1.size());
    for(int i=0;i<energy1.size();i++)
      {
	if(energy1[i] && energy2[i])
	  {
	    for (int max=i+(gateTime/binTime);i<energy.size() && i<max;i++){result[i]=true;}
	  }
	else{result[i]=false;}
      }
    return result;
  }


std::vector<bool> anti_coincidence(std::vector<bool> &energy1,std::vector<bool> &energy2, double gateTime, double binTime)
  {
<<<<<<< HEAD
    
=======
    std::vector<bool> result(energy1.size());
>>>>>>> e70ed38e58cfbaa52e6211db21d313aaeb693e09
    for(int i=0;i<energy1.size();i++)
      {
	if(energy1[i] && !energy2[i])
	  {
	    for (int max=i+(gateTime/binTime);i<energy1.size() && i<max;i++){result[i]=true;}
	  }
	else{result[i]=false;}
      }
    return result;
  }


std::vector<bool> coincidence(std::vector<double> &energy1,std::vector<double> &energy2, double gateTime, double binTime){
for (int i=0;energy1.size();i++)
{
   std::vector<bool> result(energy.size();
   if (energy1[i] && energy2[i])
    { 
          
          for (int max=i+(gateTime/binTime);i<energy1.size() && i<max;i++){result[i]=true;}

     }
      else result[i]=true;


}

return result;
}
