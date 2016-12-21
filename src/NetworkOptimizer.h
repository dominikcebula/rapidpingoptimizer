/*
 * RapidPingOptimizer
 *
 * Dominik Cebula
 * dominikcebula@gmail.com
 *
 * Licensed under GNU General Public License v2
 *
 */

#ifndef _NETWORKOPTIMIZER_H_
#define _NETWORKOPTIMIZER_H_

#include <Windows.h>
#include <string>

#define KEY_OPTIMIZER "SYSTEM\\CurrentControlSet\\services\\Tcpip\\Parameters\\Interfaces\\"

using namespace std;

class NetworkOptimizer
{
private:
	string guid;
	HKEY key;
public:
	NetworkOptimizer(string& guid);
	~NetworkOptimizer(void);

	bool optimized();
	void optimize(DWORD onoff);
};

#endif
