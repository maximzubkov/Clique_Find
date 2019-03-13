#ifndef __CLIQUEINFO_H__
#define __CLIQUEINFO_H__

struct CliqueInfo {
	int clique;
	int size;
	int mask;
	bool operator<(const CliqueInfo& a) const
    {
        return mask < a.mask;
    }
};

#endif
