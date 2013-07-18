#include <stdio.h>
#include "iniFile.h"
#include <stdlib.h>

IniFile* loadIni(char* iniAddress)
{
	IniFile* myIniFile = new IniFile();
	IniSection* sectionAddress;
	FILE* newIniFile = fopen(iniAddress, "rt");
	fseek(newIniFile, 0, SEEK_END);
	int iniSize = ftell(newIniFile);
	fseek(newIniFile, 0, SEEK_SET);
	
	char* iniData =(char*)malloc(iniSize + 1);
	memset(iniData, '\0', (iniSize + 1));
	fread(iniData, 1, iniSize, newIniFile);
	fclose(newIniFile);
	
	char* sectionBuff;
	int keyPosition;
	int lastNull;
	int sectionLength = 0;
	int sectionPosition = 0;
	int lineCount = 1;
	int sectionCount = 0;
	int keyCount = 0;
	
	for (int i = 0; i < iniSize; i++)
	{
		if (iniData[i] == '\n')
		{
			iniData[i] = '\0';
		}
	}

	for (int i = 0; i < iniSize; i++)
	{
		if (iniData[i] == '[')
		{
			sectionCount ++;
			sectionPosition = i+1;
			sectionBuff = &iniData[sectionPosition];
			int sectionLength = strlen(sectionBuff);
			if (sectionBuff[sectionLength-1] != ']')
			{
				printf("Error in ini file at section number %d", sectionCount);

			}else
			{
					sectionBuff[sectionLength-1] = '\0';                             //Removes the ']';
			}
			
			myIniFile->addSection(sectionBuff);
		}
		if(iniData[i] == '\0')
		{
			lastNull = i;
		}
		if (iniData[i] == '=')
		{
			keyCount ++;
			int keyNameLength = i - lastNull - 1;              // the = ' - 1' removes the '\0' from the beginning of the key name
			if (iniData[i-1] == ' ')
			{
				iniData[i-1] = '\0';
			}
			if (iniData[i+1] == ' ')
			{
				keyPosition = i + 2;                          //sets position past the '=' and the ' '
			}else
			{
				keyPosition = i + 1;                          // User error, forgot the ' ', so set position past the '=' only
			}
			char* keyName = &iniData[i - keyNameLength + 1];   //+ 1 is for the tab
			char* keyValue = &iniData[keyPosition];
			sectionAddress = myIniFile->getSection(sectionBuff);
			sectionAddress->addKey(keyName, keyValue);
		}
	}
	
	free(iniData);
	return myIniFile;
}


void saveIni(IniFile* ini, char* iniAddress) {
	FILE* newIniFile = fopen(iniAddress, "w");
	int sectionCount = ini->getSectionCount();

	for (int i = 0; i < sectionCount; i ++) {
		fwrite("[",1,1,newIniFile);
		char *name = ini->getSectionFromNum(i)->getSectionName();
		fwrite(name, strlen(name), 1, newIniFile);
		fwrite("]\n",2,1,newIniFile);
		int keyCount = ini->getSectionFromNum(i)->getkeyCount();
		for (int j = 0; j < keyCount; j ++) {
			char *key = ini->getSectionFromNum(i)->getKey(j)->getName();
			char *value = ini->getSectionFromNum(i)->getKey(j)->getValue();
			fwrite ("\t", 1, 1, newIniFile);
			fwrite (key, strlen(key), 1, newIniFile);
			fwrite (" = ", 3, 1, newIniFile);
			fwrite (value, strlen(value), 1, newIniFile);
			fwrite ("\n", 1, 1, newIniFile);
		}
	}
	fclose(newIniFile);
}
