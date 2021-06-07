#include "corsostudio.h"

void Corsostudio::addsetcorsi (std::string corsoid, int pos)
{
	this->setcorsi[pos].push_back(corsoid);
}
