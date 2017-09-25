#include "ServerBrowserService.h"



ServerBrowserService::ServerBrowserService()
{
	serverCount = 0;
}


ServerBrowserService::~ServerBrowserService()
{
}

bool ServerBrowserService::registerServer(ServerInfo newServer)
{
	if (serverCount == SERVERINFO_CAPACITY)
	{
		return 1;
	}
	else
	{
		servers[serverCount] = newServer;
		++serverCount;
		return 0;
	}
}

int ServerBrowserService::getServers(ServerInfo* dstArray, size_t dstSize, int maxResults, float pingLimit,
	int region, bool allowEmpty, bool allowFull, int sortType)
{
	int i = 0;
	int dstI = 0;
	for (i; dstI < dstSize && i < SERVERINFO_CAPACITY && dstI < maxResults; ++i)
	{
		if (servers[i].ping <= pingLimit &&
			(region < 0 || servers[i].region == region) &&
			(allowEmpty || servers[i].playerCount > 0) &&
			(allowFull  || servers[i].playerCount < servers[i].maxPlayers))
		{
			dstArray[dstI] = servers[i];
			++dstI;
		}
	}

	if (sortType == 1)
	{
		ServerInfo placeholder;
		for (int n = 0; n < dstI; ++n)
		{
			for (int q = 1; q < dstI; ++q)
			{
				if (dstArray[q].playerCount > dstArray[q - 1].playerCount)
				{
					placeholder = dstArray[q];
					dstArray[q] = dstArray[q - 1];
					dstArray[q - 1] = placeholder;
				}
			}
		}
	}
	else if (sortType == -1)
	{
		ServerInfo placeholder;
		for (int n = 0; n < dstI; ++n)
		{
			for (int q = 1; q < dstI; ++q)
			{
				if (dstArray[q].playerCount < dstArray[q - 1].playerCount)
				{
					placeholder = dstArray[q];
					dstArray[q] = dstArray[q - 1];
					dstArray[q - 1] = placeholder;
				}
			}
		}
	}
	else if (sortType == 2)
	{
		ServerInfo placeholder;
		for (int n = 0; n < dstI; ++n)
		{
			for (int q = 1; q < dstI; ++q)
			{
				if (dstArray[q].ping > dstArray[q - 1].ping)
				{
					placeholder = dstArray[q];
					dstArray[q] = dstArray[q - 1];
					dstArray[q - 1] = placeholder;
				}
			}
		}
	}
	else if (sortType == -2)
	{
		ServerInfo placeholder;
		for (int n = 0; n < dstI; ++n)
		{
			for (int q = 1; q < dstI; ++q)
			{
				if (dstArray[q].ping < dstArray[q - 1].ping)
				{
					placeholder = dstArray[q];
					dstArray[q] = dstArray[q - 1];
					dstArray[q - 1] = placeholder;
				}
			}
		}
	}
	else if (sortType == 3)
	{
		ServerInfo placeholder;
		for (int n = 0; n < dstI; ++n)
		{
			for (int q = 1; q < dstI; ++q)
			{
				if (isHigherOrder(dstArray[q].name, dstArray[q].nameLength,
					dstArray[q - 1].name, dstArray[q - 1].nameLength))
				{
					placeholder = dstArray[q];
					dstArray[q] = dstArray[q - 1];
					dstArray[q - 1] = placeholder;
				}
			}
		}
	}
	else if (sortType == -3)
	{
		ServerInfo placeholder;
		for (int n = 0; n < dstI; ++n)
		{
			for (int q = 1; q < dstI; ++q)
			{
				if (!isHigherOrder(dstArray[q].name, dstArray[q].nameLength,
					dstArray[q - 1].name, dstArray[q - 1].nameLength))
				{
					placeholder = dstArray[q];
					dstArray[q] = dstArray[q - 1];
					dstArray[q - 1] = placeholder;
				}
			}
		}
	}

	return 0;
}



bool ServerBrowserService::isHigherOrder(char* s1, size_t s1l, char* s2, size_t s2l)
{
	for (int i = 0; i < s1l; ++i)
	{
		if (i == s2l)
		{
			return 0;
		}

		if (s1[i] < s2[i])
		{
			return 1;
		}
	}

	if (s1l < s2l)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
