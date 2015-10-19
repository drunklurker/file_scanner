// Lotsa_dicts.cpp: ���������� ����� ����� ��� ����������� ����������.
//
//#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

struct s_params
{
	string inputDir;
	string outputDir;
	HANDLE stopEvent;
	HANDLE dirChangedEvent;
};
void chop_file(string filename, string inputDir, string outputDir);

DWORD WINAPI make_dicts(void* params) //����������� ����� � ����� � �� ���������
{
	s_params* parameters = (s_params*)params;
	//��� ������ ��������
	string filenamePattern = parameters->inputDir + "*.txt";
	WIN32_FIND_DATA fileInfo;
	HANDLE fileSearch = FindFirstFile(filenamePattern.c_str(), &fileInfo);
	while (fileSearch != INVALID_HANDLE_VALUE &&
		WaitForSingleObject(parameters->stopEvent, 0) != WAIT_OBJECT_0)
		//WaitForSingleObject � ���� ������ ���������,
		//��������� �� ����� � ���������� ���������
		//WaitForMultipleObject ��� ���������� �������
		//FindNextChangeNotification ��� ��������� ��������� �����
	{
		string filename = fileInfo.cFileName;
		chop_file(filename, parameters->inputDir, parameters->outputDir);
		if (FindNextFile(fileSearch, &fileInfo) == false)
			break;
	}
	FindClose(fileSearch);
	return 0;
}

void chop_file(string filename, string inputDir, string outputDir) //Buy for 4.99$ - SALE!
{
	throw EXCEPTION_INT_DIVIDE_BY_ZERO;

}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "������� �����:" << endl;
	string inputDir,outputDir;
	cin >> inputDir;
	cout << "�������� �����:" << endl;
	cin >> outputDir;
	HANDLE stopEvent = CreateEvent(NULL, false, false, NULL);
	HANDLE dirChangedEvent = FindFirstChangeNotification(
						inputDir.c_str(), 
						false, 
						FILE_NOTIFY_CHANGE_FILE_NAME);
	//////////////////////////////////////////////////
	s_params* threadParameters = new s_params;
	threadParameters->inputDir = inputDir;
	threadParameters->outputDir = outputDir;
	threadParameters->stopEvent = stopEvent;
	threadParameters->dirChangedEvent = dirChangedEvent;
	//////////////////////////////////////////////////
	DWORD threadID; //�� ������
	HANDLE dictThread = CreateThread(
						NULL, 
						0, 
						make_dicts, 
						threadParameters, 
						0, 
						&threadID);
	//TODO ���������� ��������� ������� � ������� ������ stopEvent
	WaitForSingleObject(dictThread, INFINITE); //���, ���� ���������� ������ �����
	CloseHandle(dictThread);
	CloseHandle(stopEvent);
	CloseHandle(dirChangedEvent);
	return 0;
}

