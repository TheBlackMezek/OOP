#pragma once



#include "ServerInfo.h"




class ServerBrowserService
{
public:
	ServerBrowserService();
	~ServerBrowserService();

	bool registerServer(ServerInfo newServer);

	int getServers(ServerInfo* dstArray, size_t dstSize, int maxResults, float pingLimit,
		int region, bool allowEmpty, bool allowFull, int sortType);

private:
	const static int SERVERINFO_CAPACITY = 20;

	ServerInfo servers[SERVERINFO_CAPACITY];

	int serverCount;

	static bool isHigherOrder(char* s1, size_t s1l, char* s2, size_t s2l);
};

