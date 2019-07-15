#include <iostream>
#include <windows.h>

using namespace std;

void ShowDevMode(DEVMODE &devMode)
{
	cout << "DEVMODE Settings:" << endl;
	cout << "  dmPelsWidth:          " << devMode.dmPelsWidth << endl;
	cout << "  dmPelsHeight:         " << devMode.dmPelsHeight << endl;
	cout << "  dmBitsPerPel:         " << devMode.dmBitsPerPel << endl;
	cout << "  dmDisplayFrequency:   " << devMode.dmDisplayFrequency << endl;
	cout << "  dmDisplayOrientation: " << devMode.dmDisplayOrientation << endl;
}

void ShowResult(long Result)
{
	switch(Result)
	{
		case DISP_CHANGE_SUCCESSFUL:
		cout << "ChangeDisplaySettingsEx returns DISP_CHANGE_SUCCESSFUL" << endl;
		break;
		case DISP_CHANGE_BADFLAGS:
		cout << "ChangeDisplaySettingsEx returns DISP_CHANGE_BADFLAGS" << endl;
		break;
		case DISP_CHANGE_BADMODE:
		cout << "ChangeDisplaySettingsEx returns DISP_CHANGE_BADMODE" << endl;
		break;
		case DISP_CHANGE_BADPARAM:
		cout << "ChangeDisplaySettingsEx returns DISP_CHANGE_BADPARAM" << endl;
		break;
		case DISP_CHANGE_FAILED:
		cout << "ChangeDisplaySettingsEx returns DISP_CHANGE_FAILED" << endl;
		break;
		case DISP_CHANGE_NOTUPDATED:
		cout << "ChangeDisplaySettingsEx returns DISP_CHANGE_NOTUPDATED" << endl;
		break;
		case DISP_CHANGE_RESTART:
		cout << "ChangeDisplaySettingsEx returns DISP_CHANGE_RESTART" << endl;
		break;
		default:
		cout << "ChangeDisplaySettingsEx - Unexpected return value." << endl;
	}
}

void rotate()
{
	DEVMODE devMode;
	long r;

	// Init DEVMODE to current settings
	ZeroMemory(&devMode, sizeof(DEVMODE));
	devMode.dmSize = sizeof(devMode);
	EnumDisplaySettingsEx(NULL, ENUM_CURRENT_SETTINGS, &devMode, NULL);
	ShowDevMode(devMode);

	/* Rotate Orientation - 0 */
	//devMode.dmDisplayOrientation = DMDO_DEFAULT;// default
	//devMode.dmPelsWidth = 1280;
	//devMode.dmPelsHeight = 1024;

	/* Rotate Orientation - 90 */
	devMode.dmDisplayOrientation = DMDO_90;
	swap(devMode.dmPelsHeight, devMode.dmPelsWidth);

	devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYORIENTATION;
	r = ChangeDisplaySettingsEx(NULL, &devMode, NULL,  CDS_UPDATEREGISTRY | CDS_GLOBAL | CDS_NORESET, NULL);
	ShowResult(r);
	r = ChangeDisplaySettingsEx("\\\\.\\DISPLAY1", NULL, NULL, NULL, NULL);
	ShowResult(r);

	// Reread current settings
	ZeroMemory(&devMode, sizeof(DEVMODE));
	devMode.dmSize = sizeof(devMode);
	EnumDisplaySettingsEx(NULL, ENUM_CURRENT_SETTINGS, &devMode, NULL);
	ShowDevMode(devMode);
}

int main(int argc, char **argv)
{
	rotate();
	cout<<"bye";
	cin.get();
	cin.get();
	return 0;
}
