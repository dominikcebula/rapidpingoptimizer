/*
 * RapidPingOptimizer
 *
 * Dominik Cebula
 * dominikcebula@gmail.com
 *
 * Licensed under GNU General Public License v2
 *
 */

#include "NetworkOptimizer.h"
#include "RegistryWrapper.h"
#include "common.h"

NetworkOptimizer::NetworkOptimizer(string& guid)
{
	this->guid=guid;
}

NetworkOptimizer::~NetworkOptimizer(void)
{
}

bool NetworkOptimizer::optimized()
{
	string key=KEY_OPTIMIZER;
	string val;
	val.resize(1, 0);
	bool ret=false;
	key.append(guid);
	RegistryWrapper reg(HKEY_LOCAL_MACHINE, key);
	reg.Open();
	try { val=reg.GetVal("TcpAckFrequency"); } catch(exception) { }
	ret=val.c_str()[0]==1;
	reg.Close();

	return ret;
}

void NetworkOptimizer::optimize(DWORD onoff)
{
	string key=KEY_OPTIMIZER;
	key.append(guid);
	try {
		RegistryWrapper reg(HKEY_LOCAL_MACHINE, key);
		reg.Open();
		reg.SetVal("TcpAckFrequency", onoff);
		reg.Close();
	} catch (exception&) {
		string err("Failed to optimize interface ");
		err.append(guid);
		WrnBox(err.c_str());
	}
}