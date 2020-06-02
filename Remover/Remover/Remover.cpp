#include <iostream>
#include <string>
#include <conio.h>
#include <locale.h>
#include <cstdio>
#include <fstream>
#include <vector> 
#include <windows.h>

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

using namespace std;

int GetOptionFromConsole(int& Option);
int GetPathFromConsole(string& Path);
int ReWriteFileFromPath(string Path, int option);
int RemoveFileFromPath(string Path);
int Gutman(ofstream& file, int length);
int DoD(ofstream& file, int length);
int VSItR(ofstream& file, int length);
int UserStandart(ofstream& file, int length);
int CryptGen(int& crypt);
int CloseFileFromPath(ofstream& OpeningFile);
int SetColor(string Text, int Color);

int main()
{
	string Path = " ";
	int option;
	int start;
	do {
		do {
			if(SetColor("1 - start\n2 - exit",Yellow) != 0)
			{
			SetColor("Error SetColor", Red);
			return 1;
		}
		cin	>> start;
		if (cin.fail()) {
			SetColor("Error cin", Red);
			return 2;
		}
	} while (!(start == 1 || start == 2));
	if (start == 2)
	{
		return 0;
	}
	if (GetPathFromConsole(Path) != 0) {
		SetColor("Error GetPathFoomConsole", Red);
		return 3;
	}
	if (GetOptionFromConsole(option) != 0)
	{
		SetColor("Error GetOptionFromConsole", Red);
		return 4;
	}
	if (option == 5)break;
	if (ReWriteFileFromPath(Path, option) != 0) {
		SetColor("Error ReWriteFileFromPath", Red);
		return 5;
	}
	/*if (RemoveFileFromPath(Path) != 0)
	{
		cout << "Error RemoveFileFromPath";
		return 6;
	}*/
	if (system("cls") != 0) {
		SetColor("Error system(\"cls\")", Red);
		return 7;
	}
	} while (option != 5);
	if(option!=5){
		SetColor("Error unknown opion!", Red);
		return 8;
	}

	return 0;
}

int GetOptionFromConsole(int& Option) {
	string accept;
	do {
		if (SetColor("Are you sure?The changes will be irreversible!(y/n)", Red) != 0) {
			SetColor("Error setcolor", Red);
			return 1;
		}
		cin >> accept;
		if (cin.fail()) {
			SetColor("Error cin", Red);
			return 2;
		}
	} while (!(accept == "y" || accept == "n"));
	if (accept == "n") {
		Option = 5;
		return 0;
	}
	do {
	
		if (SetColor("Please enter usage option: \n1 - DoD 5220.22-M\n2 - VSlyR\n3 - Gutman\n4 - User standart\n5 - exit",Yellow) != 0) {
			SetColor("Error setcolor",Red);
			return 3;
		}
		cin >> Option;
		if (cin.fail()) {
			SetColor("Error cin",Red);
			return 4;
		}
	} while (!(Option == 1 || Option == 2 || Option == 3 || Option == 4 || Option == 5));
	return 0;
}

int GetPathFromConsole(string& Path) {
	ifstream file;
	do {
		if (SetColor("Please enter valid source file path vith text:", Yellow) != 0) {
			SetColor("Error SetColor",Red);
			return 1;
		}
		cin >> Path;
		if (cin.fail()) {
			SetColor("Error cin",Red);
			return 2;
		}
		file = ifstream(Path);
	} while (!(file.good() && file.peek() != EOF));
	file.close();
	if (file.fail()) {
		SetColor("Error close file",Red);
		return 3;
	}
	return 0;
}

int  ReWriteFileFromPath(string Path, int Option) {
	ofstream OpeningFile;
	int end;
	int usernum = 0;
	char userbyte = 0;
	if (&Path == 0) {
		SetColor("Error argument Path", Red);
		return 1;
	}
	if (Option>4||Option<1) {
		SetColor("Error argument Option", Red);
		return 2;
	}
	OpeningFile.open(Path, ios::binary | ios::_Nocreate);
	if (OpeningFile.failbit == true){
		SetColor("error opening file", Red);
		return 3;
	}
	else {
		if (SetColor("File is open .Good!", Green) != 0) {
			SetColor("Error SetColor",Red);
			return 4;
		}
	}
	OpeningFile.seekp(0, ios::end);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		OpeningFile.close();
		return 5;
	}
	end = OpeningFile.tellp();
	if (end == -1) {
		SetColor("Error telp", Red);
		OpeningFile.close();
		return 6;
	}
	
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		OpeningFile.close();
		return 7;
	}

	switch (Option) {
	case 1://DoD 5220.22-M
		if (DoD(OpeningFile, end) != 0) {
			SetColor("Error DoD", Red);
			OpeningFile.close();
			return 8;
		}
		break;
	case 2://VSItR
		if (VSItR(OpeningFile, end) != 0) {
			SetColor("Error VSItR", Red);
			OpeningFile.close();
			return 9;
		}

		break;
	case 3://Gutman
		if (Gutman(OpeningFile, end) != 0) {
			SetColor("Error Gutman", Red);
			OpeningFile.close();
			return 10;
		}
		break;
	case 4://User standart
		if (UserStandart(OpeningFile, end) != 0) {
			SetColor("Error Userstandart", Red);
			OpeningFile.close();
			return 11;
		}
		break;
	default:
		SetColor("Error.Unknown option", Red);
		OpeningFile.close();
		return 12;
		break;
	}
	if (CloseFileFromPath(OpeningFile) != 0) {
		SetColor("Error CloseFileFromPath", Red);
			return 13;
	}
	return 0;
}

int CryptGen(int &Crypt) {
	DWORD len = 1;
	BYTE  pbData[1] = {0};
	HCRYPTPROV   hCryptProv;
	if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0)) 
	{
		if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET))
		{
			SetColor("Error CryptAcquireContex", Red);
			return 1;
		}
	}

	if (!CryptGenRandom(hCryptProv, len, pbData))
	{
		SetColor("Error CryptGenRandom", Red);
		CryptReleaseContext(hCryptProv, len);
		return 2;
	}
	Crypt = pbData[0];
	len = 0;
	if (CryptReleaseContext(hCryptProv, len) == 0) {
		SetColor("Error CryptReleaseContext", Red);
		return 3;
	}
	return 0;
}

int Gutman(ofstream& OpeningFile,int end) {
	int cryptnum;
	if (&OpeningFile == 0) {
		SetColor("Error argument OpeningFile", Red);
		return 1;
	}
	if (end == 0) {
		SetColor("Error argument end", Red);
		return 2;
	}
	// шаг 1-4
	for (size_t j = 0; j < 4; j++) {
		for (int i = 0; i < end; i++) {
			if (CryptGen(cryptnum)!=0)
			{
				SetColor("Error CryptGen", Red);
				return 3;
			}
			OpeningFile.put(cryptnum);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 4;
			}
		}
		OpeningFile.seekp(0, ios::beg);
		if (OpeningFile.fail()) {
			SetColor("Error seekp", Red);
			return 5;
		}
	}

	// шаг 5-6
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(char(0x55));
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 6;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 7;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0xAA);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 8;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 9;
	}
	// 7 шаг
	for (size_t i = 0; i < end; i++) {
		if ((i + 2) % 3 == 0) {
			OpeningFile.put(0x92);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 10;
			}
		}
		else if ((i + 1) % 3 == 0) {
			OpeningFile.put(0x49);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 11;
			}
		}
		else {
			OpeningFile.put(0x24);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 12;
			}
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 13;
	}
	// 8 шаг
	for (size_t i = 0; i < end; i++) {
		if ((i + 2) % 3 == 0) {
			OpeningFile.put(0x49);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 14;
			}
		}
		else if ((i + 1) % 3 == 0) {
			OpeningFile.put(0x24);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 15;
			}
		}
		else {
			OpeningFile.put(0x92);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 16;
			}
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 17;
	}
	// 9 шаг
	for (size_t i = 0; i < end; i++) {
		if ((i + 2) % 3 == 0) {
			OpeningFile.put(0x24);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 18;
			}
		}
		else if ((i + 1) % 3 == 0) {
			OpeningFile.put(0x92);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 19;
			}
		}
		else {
			OpeningFile.put(0x49);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 20;
			}
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 21;
	}
	// шаг 10-25
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0x00);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 22;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 23;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0x11);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 24;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 25;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0x22);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 26;
		}
	}
	OpeningFile.seekp(0, ios::beg); {
		if (OpeningFile.fail()) {
			SetColor("Error seekp", Red);
			return 27;
		}
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0x33);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 28;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 29;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0x44);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 30;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 31;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0x55);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 32;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 33;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0x66);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 34;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 35;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0x77);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 36;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 37;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0x88);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 38;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 39;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0x99);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 40;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 41;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0xAA);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 42;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 43;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0xBB);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 44;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 45;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0xCC);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 46;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 47;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0xDD);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 48;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 49;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0xEE);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 50;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 51;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0xFF);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 52;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 53;
	}
	// шаг 26
	for (size_t i = 0; i < end; i++) {
		if ((i + 2) % 3 == 0) {
			OpeningFile.put(0x92);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 54;
			}
		}
		else if ((i + 1) % 3 == 0) {
			OpeningFile.put(0x49);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 55;
			}
		}
		else {
			OpeningFile.put(0x24);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 56;
			}
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error skeep", Red);
		return 57;
	}
	// шаг 27
	for (size_t i = 0; i < end; i++) {
		if ((i + 2) % 3 == 0) {
			OpeningFile.put(0x92);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 58;
			}
		}
		else if ((i + 1) % 3 == 0) {
			OpeningFile.put(0x49);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 59;
			}
		}
		else {
			OpeningFile.put(0x24);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 60;
			}
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 61;
	}
	// шаг 28
	for (size_t i = 0; i < end; i++) {
		if ((i + 2) % 3 == 0) {
			OpeningFile.put(0x92);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 62;
			}
		}
		else if ((i + 1) % 3 == 0) {
			OpeningFile.put(0x49);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 63;
			}
		}
		else {
			OpeningFile.put(0x24);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 64;
			}
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 65;
	}
	// шаг 29
	for (size_t i = 0; i < end; i++) {
		if ((i + 2) % 3 == 0) {
			OpeningFile.put(0x6D);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 66;
			}
		}
		else if ((i + 1) % 3 == 0) {
			OpeningFile.put(0xB6);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 67;
			}
		}
		else {
			OpeningFile.put(0xDB);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 68;
			}
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 69;
	}
	// шаг 30
	for (size_t i = 0; i < end; i++) {
		if ((i + 2) % 3 == 0) {
			OpeningFile.put(0xB6);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 70;
			}
		}
		else if ((i + 1) % 3 == 0) {
			OpeningFile.put(0xDB);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 71;
			}
		}
		else {
			OpeningFile.put(0x6D);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 72;
			}
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 73;
	}
	// шаг 31
	for (size_t i = 0; i < end; i++) {
		if ((i + 2) % 3 == 0) {
			OpeningFile.put(0xDB);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 74;
			}
		}
		else if ((i + 1) % 3 == 0) {
			OpeningFile.put(0x6D);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 75;
			}
		}
		else {
			OpeningFile.put(0xB6);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 76;
			}
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 77;
	}
	// шаг 32-35
	for (size_t j = 0; j < 5; j++) {
		for (size_t i = 0; i < end; i++) {
			if (CryptGen(cryptnum)!=0)
			{
				SetColor("Error CryptGen", Red);
				return 78;
			}
			OpeningFile.put(cryptnum);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 79;
			}
		}
		OpeningFile.seekp(0, ios::beg);
		if (OpeningFile.fail()) {
			SetColor("Error skeep", Red);
			return 80;
		}
	}
	return 0;
}

int DoD(ofstream& OpeningFile, int end) {
	int cryptnum;
	if (&OpeningFile == 0) {
		SetColor("Error argument OpeningFile", Red);
		return 1;
	}
	if (end == 0) {
		SetColor("Error argument end", Red);
		return 2;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0x00);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 3;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 4;
	}
	for (size_t i = 0; i < end; i++) {
		OpeningFile.put(0xFF);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 5;
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 6;
	}
	for (size_t i = 0; i < end; i++) {
		if (CryptGen(cryptnum))
		{
			SetColor("Error CryptGen", Red);
			return 7;
		}
		OpeningFile.put(cryptnum);
		if (OpeningFile.fail())
		{
			SetColor("Error put", Red);
			return 8;
		}
	}
	return 0;
}

int VSItR(ofstream& OpeningFile, int end) {
	int cryptnum;
	if (&OpeningFile == 0) {
		SetColor("Error argument OpeningFile", Red);
		return 1;
	}
	if (end == 0) {
		SetColor("Error argument end", Red);
		return 2;
	}
	for (size_t j = 0; j <= 2; j++) {
		OpeningFile.seekp(0, ios::beg);
		for (size_t i = 0; i < end; i++) {
			OpeningFile.put(0x00);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 3;
			}
		}
		OpeningFile.seekp(0, ios::beg);
		if (OpeningFile.fail()) {
			SetColor("Error seekp", Red);
			return 4;
		}
		for (size_t i = 0; i < end; i++) {
			OpeningFile.put(0xFF);
			if (OpeningFile.fail()) {
				SetColor("Error put", Red);
				return 5;
			}
		}
	}
	OpeningFile.seekp(0, ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 6;
	}
	for (size_t i = 0; i < end; i++) {
		if (CryptGen(cryptnum) != 0)
		{
			SetColor("Error CryptGen", Red);
			return 7;
		}
		OpeningFile.put(cryptnum);
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 8;
		}
	}
	return 0;
}

int UserStandart(ofstream& OpeningFile, int end) {
	vector <string> nums;
	string usernum;
	char num = ' ';
	int proverka = 0;
	int j = 0;
	int i = 0;
	if (&OpeningFile == 0) {
		SetColor("Error argument OpeningFile", Red);
		return 1;
	}
	if (end == 0) {
		SetColor("Error argument end", Red);
		return 2;
	}
	do {
		cin.ignore(256, '\n');
		nums.clear();
		proverka = 0;
		i = 0;
		j = 0;
		if (SetColor("Enter your nums (0 to 255) separated by a space:", Yellow) != 0)
		{
			SetColor("Error SetColor", Red);
			return 3;
		}
		if (getline(cin, usernum).eof()) {
			SetColor("Error getline", Red);
			return 4;
		}
		while (i <= usernum.length()) {
			if (usernum[i] == ' ' || i == usernum.length()) {
				if (atoi(usernum.substr(j, i - j).c_str()) > 255 || atoi(usernum.substr(j, i - j).c_str()) < 0) {
					proverka++;
					break;
				}
				cout << atoi(usernum.substr(j, i - j).c_str());
				nums.push_back(usernum.substr(j, i - j));
				j = i;
			}
			i++;
		}
		if (proverka != 0) {
			if (SetColor("You write invalid value.Press enter for try again!", Red) != 0) {
				SetColor("Error SetColor", Red);
				return 5;
			}
		}
	} while (proverka != 0);

	OpeningFile.seekp(ios::beg);
	if (OpeningFile.fail()) {
		SetColor("Error seekp", Red);
		return 6;
	}
	for (size_t i = 0,j=0; i < end; i++,j++) {
		
		if (j == nums.size()) {
			j = 0;
		}
	
        OpeningFile.put((char)atoi(nums[j].c_str()));
		if (OpeningFile.fail()) {
			SetColor("Error put", Red);
			return 7;
		}
	}
	return 0;
}

int CloseFileFromPath(ofstream &OpeningFile) {
	if (&OpeningFile == 0) {
		SetColor("Error argument OpeningFile", Red);
		return 1;
	}
	OpeningFile.close();
	if (OpeningFile.fail()) {
		SetColor("Error close file",Red);
		return 2;
	}
	else {
		if (SetColor("File close.Good!", Green) != 0) {
			SetColor("Error SetColor", Red);
			return 3;
		}
	}
	return 0;
}

int RemoveFileFromPath(string Path) {
	if (&Path == 0) {
		SetColor("Error argument Path",Red);
		return 1;
	}
	if (remove(Path.c_str()) != 0) {
		SetColor("Error remove file",Red);
		return 2;
	}
	else {
		if (SetColor("File remove.Good!", Green) != 0) {
			SetColor("Error SetColor", Red);
			return 3;
		}
	}
	return 0;
}

int SetColor(string text, int Color) {
	if (Color<0||Color>15){
		cout << "Error argument color";
		return 1;
	}
	if (SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color) == 0) {
		cout << "Error SetConsoleTextAttribute";
		return 2;
	}
	cout << text << endl;
	if (cout.fail()) {
		cout << "Error cout";
		return 3;
	}
	if (SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleColor(White)) == 0) {
		cout << "Error SetConsoleTextAttribute";
		return 4;
	}
	return 0;
}