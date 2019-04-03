#include "CliqueInfo.h"
#include <iostream>
#include <cstdint>
using namespace std;
CliqueInfo::CliqueInfo(){}
CliqueInfo::CliqueInfo(uint64_t clique, std::size_t size, uint64_t mask, size_t max, uint64_t all):
	clique(clique),
	size(size),
	mask(mask),
	max(max),
	all(all)
{}

std::ostream& operator << (std::ostream &ostr, const CliqueInfo &cli)
{
	int i = 0;
	uint64_t num = cli.mask;
	int max = cli.max;
	ostr << "clique of " << cli.size << " size\nmask: (";
	while (num > 0){
		if ((num & 1ULL) == 1ULL){
			if (num > 1){
				ostr << max - i - 1<<",";
			} else {
				ostr << max - i - 1;
			}
		}
		i++;
		num = num >> 1;
	}
	ostr << ")\n";
	num = cli.all;
	ostr << "all: (";
	while (num > 0){
		if ((num & 1ULL) == 1ULL){
			if (num > 1){
				ostr << max - i - 1<<",";
			} else {
				ostr << max - i - 1;
			}
		}
		i++;
		num = num >> 1;
	}
	ostr << ")\n";
	num = cli.clique;
	ostr << "clique: (";
	while (num > 0){
		if ((num & 1ULL) == 1ULL){
			if (num > 1){
				ostr << max - i - 1<<",";
			} else {
				ostr << max - i - 1;
			}
		}
		i++;
		num = num >> 1;
	}
	ostr << ")\n";
	return ostr;
}


// CliqueInfo operator= (const CliqueInfo& cli){
// 	return CliqueInfo(this->clique = cli.clique, 
// 					  this->size = cli.size, 
// 					  this->mask = cli.mask, 
// 					  this->max = cli.max, 
// 					  this->all = cli.all);
// }
