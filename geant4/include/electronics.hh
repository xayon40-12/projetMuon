#ifndef ELECTRONICS_HH
#define ELECTRONICS_HH

std::vector<bool> gate(std::vector<double> &energy, double threshold, double gateTime, double binTime);
std::vector<bool> coincidence(std::vector<bool> &energy1,std::vector<bool> &energy2, double gateTime, double binTime);
std::vector<bool> anti_coincidence(std::vector<bool> &energy1,std::vector<bool> &energy2, double gateTime, double binTime); // 1 && not 2
std::vector<bool> timer(std::vector<bool> &start, std::vector<bool> &stop, double gateTime, double binTime);

#endif
