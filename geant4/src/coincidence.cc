#include "electronics.hh"

std::vector<bool> coincidence(std::vector<double> &energy1,std::vector<double> &energy2, double gateTime, double binTime){
for (int i=0;energy1.size();i++)
{
   if (energy1[i] && energy2[i])
    { 
          coincidence[i]=true;
          
     }
   if (energy1[i]=true && energy2[i]=false)
  {
    

   }

   else coincidence[i]=true;


}


}
