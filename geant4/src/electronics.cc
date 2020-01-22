#include "electronics.hh"

std::vector<bool> gate(std::vector<double> &energy, double threshold, double gateTime, double binTime)
{
  std::vector<bool> result(energy.size());

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
    std::vector<bool> result(energy1.size());
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

std::vector<double> timer(std::vector<bool> &start, std::vector<bool> &stop, double gateDeadTime, double binTime)
{
  double time=0.0;
  bool trig=false;
  std::vector<double> times;
  for(int i=0;start.size();i++)
    {
      if(start[i] && !trig)
	{
	  trig=true;
	  time=i;
	}
      if(stop && trig)
	{
	  trig=false;
	  time=(i-time)*binTime;
	  times.push_back(time);
	  i+=gateDeadTime/binTime;
	} 
    }
  return times;
}