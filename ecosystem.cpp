#include <iostream>
#include "functs.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
	int DoS;
	srand(time(NULL));

	Ecosystem *MyEcosystem;
	MyEcosystem=new Ecosystem();

	MyEcosystem->print_map();

	
	//ARXIKO PLH8OS FYTWN KAI ZWWN
	MyEcosystem->PlacePlants(40,40,40,40,40);	//cout<<"plants plced"<<endl;
	MyEcosystem->PlaceAnimals(15,15,10,15,3,3,3);	//cout<<"animals placed"<<endl;

	MyEcosystem->printTilesp();
	cout << endl << "///////////////////" << endl << endl;
	MyEcosystem->PrintSystem();
	MyEcosystem->PrintPlantStatistics();
	MyEcosystem->PrintAnimalStatistics();
	MyEcosystem->printAnimals();

	cout << endl << "Give days of stimulation" << endl;
	cin>> DoS;
	MyEcosystem->RunEcosystem(DoS,3);//hmeres proswmoioshs , epoxh (1.Anoiksh 2.Kalokairi 3.F8inopwro 4.Xeimwnas)

//	MyEcosystem->printAnimals();

//	MyEcosystem->print_map();
//	MyEcosystem->printTilesp();

	MyEcosystem->PrintSystem();
	MyEcosystem->PrintPlantStatistics();
	MyEcosystem->PrintAnimalStatistics();

	MyEcosystem->delete_map();
	delete MyEcosystem;	
}
