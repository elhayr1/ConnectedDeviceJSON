#include "devices_tree.h"
#include "JSON.h"

int main()
{
	DevicesTree tree;
	tree.feedTree();
	//tree.printTree(tree.root());
	//std::string jsonOut;
	JSONObject jsonOut;
	tree.devicesTreeToJSON(tree.root(), jsonOut);
	//std::cout << jsonOut << "\n\n";

    /*
	std::wstring convertor = std::wstring(jsonOut.begin(), jsonOut.end());
	const wchar_t* widecstr = convertor.c_str();
	JSONValue *value = JSON::Parse(widecstr);
	std::wcout << value->Stringify(true).c_str();*/
	JSONValue *out = new JSONValue(jsonOut);
	std::wcout << out->Stringify(true).c_str();
	
	return 0;
}