#pragma once






class PiggyBank
{
public:
	PiggyBank();
	~PiggyBank();

	void deposit(float m);
	float empty();
	const float balance();

private:
	float money;
};

