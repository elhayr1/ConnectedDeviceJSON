//-------------------------
//Created by: Elchay Rauper
//-------------------------

#include <iostream>
#include <fstream>
#include "devices_tree.h"
#include "JSON.h"

//edit next lines in order to print to file
#define PRINT_TO_FILE true
#define FILE_PATH "output_file.txt"

int main()
{
	
	//get data structure ready
	DevicesTree tree;
	tree.feedTree();

	//enable this line to print devices tree as raw data
	//tree.printTree(tree.root()); 
	
	JSONObject jsonOut;
	tree.devicesTreeToJSON(tree.root(), jsonOut);
	
	JSONValue *out = new JSONValue(jsonOut);

	if (PRINT_TO_FILE)
	{
		std::wofstream outFile;
		outFile.open(FILE_PATH);
		if (outFile.is_open())
		{
			outFile << out->Stringify(true).c_str();
			if (!outFile.good())
				std::cout << "\nSome error ocurred while trying to write to file.\n";
			else
				std::cout << "\nWriting connected file to file ended successfuly\n";
		}
		else
			std::cout << "Error: can't open file at " << FILE_PATH << "\nCheck file path.\n";
	}
	else
		std::wcout << out->Stringify(true).c_str();
	
	return 0;
}