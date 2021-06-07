#ifndef CORSO_STUDIO_H
#define CORSO_STUDIO_H
#include <list>
#include <iostream>
#include <string>
#include <vector>

class Corsostudio
{
public:
	void addsetcorsi(std::string corsoid, int pos);
	std::string generateidcorsostudio();

private:
	std::string idcorsostudio;
	std::vector<std::list<std::string>> setcorsi;
	std::vector<std::string> corsispenti;
};

#endif

