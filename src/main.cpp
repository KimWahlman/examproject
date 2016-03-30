#include "CellularAutomata\CellularAutomata.h"
#include "DLA\DLA.h"
#include "Misc\misc.h"
#include "SFMLStuff.h"

int main()
{
	/// - CA Example Usage -
	FileReader::GetInstance().ReadFromFile("data.txt", 100);
	std::srand((unsigned int)time(0));
	//// SizeX, SizeY, BirthLimit, DeathLimit, Generations, Initial Survivial Rate, Caves to Generate, Seed
	CellularAutomata::GetInstance().Init( FileReader::GetInstance().FetchIntData(0),
								FileReader::GetInstance().FetchIntData(1),
								FileReader::GetInstance().FetchIntData(2),
								FileReader::GetInstance().FetchIntData(3),
								FileReader::GetInstance().FetchIntData(4),
								FileReader::GetInstance().FetchIntData(5),
								FileReader::GetInstance().FetchIntData(6),
								FileReader::GetInstance().FetchIntData(7) );
	
	CellularAutomata::GetInstance().LifeCycle();
	Calculations::GetInstance().FindTime("Data/" + std::to_string(CellularAutomata::GetInstance().GetSizeX()) + "x" + std::to_string(CellularAutomata::GetInstance().GetSizeY()) + "_data.txt", CellularAutomata::GetInstance().GetSizeX(), CellularAutomata::GetInstance().GetSizeY(), FileReader::GetInstance().FetchIntData(6));
	/// - CA Example Usage -

	/// - DLA Example Usage -
	//DLA::GetInstance().LifeCycle();
	//Calculations::GetInstance().FindTime("Data/" + std::to_string(DLA::GetInstance().GetSizeX()) + "x" + std::to_string(DLA::GetInstance().GetSizeY()) + "_data.txt", DLA::GetInstance().GetSizeX(), DLA::GetInstance().GetSizeY(), FileReader::GetInstance().FetchIntData(2));
	/// - DLA Example Usage -

	std::cin.get();
	return 0;
}
