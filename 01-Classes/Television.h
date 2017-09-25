#pragma once





class Television
{
public:
	Television();
	~Television();

	void incVolume();
	void decVolume();

	void incChannel();
	void decChannel();

private:
	int channel;
	int volume;
};

