Software design summary, and some guidelines:

devices_parser - extract connected devices data.

devices_tree - main logic class. stores data in tree data structure, and allows conversion of data to JSON format by 
scanning the tree. Each device instance ID represented as a path, which is then breaked to parts and stored in tree.
For example: assume we have connected device instance ID x/y/1, the class will store it in tree as:
|device node 1| --parent--> |path node y| --parent--> |path node x|.

main - prepare data structure, and allow user to choose whether to print JSON to console or to file.
In order to print to console, set PRINT_TO_FILE macro to false (default). In order to print to file,
set PRINT_TO_FILE to true, and FILE_PATH to the file path. Example file is located in Resources Files folder 
and is named output_file.txt.