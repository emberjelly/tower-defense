#ifndef INIFILE_H
#define INIFILE_H

#include <string.h>
#include <stdio.h>


class IniKeyValuePair
{
public:
	IniKeyValuePair()
	{
		m_pNameBuffer = NULL;
		m_pValueBuffer = NULL;
	}

	~IniKeyValuePair()
	{
		if (m_pNameBuffer != NULL)
		{
			delete[] m_pNameBuffer;
			m_pNameBuffer = NULL;
		}

		if (m_pValueBuffer != NULL)
		{
			delete[] m_pValueBuffer;
			m_pValueBuffer = NULL;
		}
	}

	char* getName()
	{
		return m_pNameBuffer;
	}

	void setName(char* newName)
	{
		if (m_pNameBuffer != NULL)
		{
			delete[] m_pNameBuffer;
			m_pNameBuffer = NULL;
		}

		size_t bufSize = strlen(newName) + 1;
		m_pNameBuffer = new char[bufSize];

		strcpy_s(m_pNameBuffer, bufSize, newName);
	}

	char *getValue()
	{
		return m_pValueBuffer;
	}

	void setValue(char* newValue)
	{
		if (m_pValueBuffer != NULL)
		{
			delete[] m_pValueBuffer;
			m_pValueBuffer = NULL;
		}

		int bufSize = strlen(newValue) + 1;
		m_pValueBuffer = new char[bufSize];

		strcpy_s(m_pValueBuffer, bufSize, newValue);
	}

private:
	char* m_pNameBuffer;
	char* m_pValueBuffer;
};


class IniSection
{
public:
	IniSection()
	{
		m_ppKeys = NULL;
		m_pSectionNameBuffer = NULL;
		m_KeyCount = 0;

	}

	~IniSection()
	{
		
		if (m_pSectionNameBuffer != NULL)
		{
			delete[] m_pSectionNameBuffer;
			m_pSectionNameBuffer = NULL;
		}

		if (m_ppKeys != NULL)
		{
			delete[] m_ppKeys;
			m_ppKeys = NULL;
		}
	}

	void addKey(char* keyName, char* keyValue)
	{	
		m_KeyCount ++;
		IniKeyValuePair** m_ppTemp = m_ppKeys;
		m_ppKeys = new IniKeyValuePair*[m_KeyCount];
		for (int i = 0; i < (m_KeyCount - 1); i ++)
		{
			m_ppKeys[i] = new IniKeyValuePair();
			*m_ppKeys[i] = *m_ppTemp[i];
		}

		m_ppKeys[m_KeyCount-1] = new IniKeyValuePair();
		m_ppKeys[m_KeyCount-1]->setName(keyName);
		m_ppKeys[m_KeyCount-1]->setValue(keyValue);
		if (m_ppTemp !=NULL)
		{
			delete[] m_ppTemp;
		}
		

	}

	void removeKey(char* keyName)
	{
		int cmpResult;
		int temp = m_KeyCount;
		for(int i = 0; i < temp; i ++)
		{
			cmpResult = strcmp (keyName, m_ppKeys[i][0].getName());
			if (cmpResult == 0)
			{
				m_KeyCount --;
				for (int j = 0; j < (m_KeyCount); j++)
				{
				*m_ppKeys[j] = *m_ppKeys[j+1];
				}
			}
		}
	}

	void setSectionName(char* newSectionName)
	{
		if (m_pSectionNameBuffer != NULL)
		{
			delete[] m_pSectionNameBuffer;
			m_pSectionNameBuffer = NULL;
		}

		size_t bufSize = strlen(newSectionName) + 1;
		m_pSectionNameBuffer = new char[bufSize];

		strcpy_s(m_pSectionNameBuffer, bufSize, newSectionName);
	}

	char* getSectionName()
	{
		return m_pSectionNameBuffer;
	}

	IniKeyValuePair* getKey(int keyNumber)
	{
		return m_ppKeys[keyNumber];
	}

	int getkeyCount()
	{
		return m_KeyCount;
	}

private:
	IniKeyValuePair** m_ppKeys;
	int m_KeyCount;
	char* m_pSectionNameBuffer;
};


class IniFile
{
public:

	IniFile()
	{
		m_ppIniSection = NULL;
		m_SectionCount = 0;
	}

	~IniFile()
	{
		if (m_ppIniSection != NULL)
		{
			delete[] m_ppIniSection;
			m_ppIniSection = NULL;
		}
	}

	void addSection(char* newSection)
	{
		m_SectionCount ++;
		IniSection** temp = m_ppIniSection;
		
		m_ppIniSection = new IniSection*[m_SectionCount];
		

		for (int i = 0; i < (m_SectionCount - 1); i ++)
		{
			m_ppIniSection[i] = new IniSection();
			m_ppIniSection[i] = temp[i];
		}

		m_ppIniSection[m_SectionCount - 1] = new IniSection();
		m_ppIniSection[m_SectionCount - 1]->setSectionName(newSection);
		
		if (temp !=NULL)
		{
			delete[] temp;
		}
	}
		
	
	IniSection* getSection(char* sectionName)
		{
			char* tempSection;
			for (int i = 0; i < m_SectionCount; i ++)
			{
				tempSection = m_ppIniSection[i]->getSectionName();
				if (strcmp(tempSection, sectionName) == 0)
				{
					return m_ppIniSection[i];
				}
			}
			printf("IniSection not found, returning section number 1");
			return m_ppIniSection[0];
		}
	IniSection* getSectionFromNum (int sectionNumber)
	{
		return m_ppIniSection[sectionNumber];
	}

	int getSectionCount()
	{
		return m_SectionCount;
	}

	void saveIni(char* saveAddress)
	{
		FILE* saveIniFile = fopen (saveAddress, "w");
		char* keyName = NULL;
		char* keyValue = NULL;
		for (int sections = 0; sections < m_SectionCount; sections ++)
		{
			fwrite("[", 1, 1, saveIniFile);
			fwrite(m_ppIniSection[sections]->getSectionName(), 1,strlen(m_ppIniSection[sections]->getSectionName()), saveIniFile);
			fwrite("]\n", 1,2 , saveIniFile);
			for (int keys = 0; keys < m_ppIniSection[sections]->getkeyCount(); keys ++)
			{
				keyName = m_ppIniSection[sections]->getKey(keys)->getName();
				keyValue = m_ppIniSection[sections]->getKey(keys)->getValue();
				fwrite(keyName, strlen(keyName), 1, saveIniFile);
				fwrite(" = ", 1, 3, saveIniFile);
				fwrite(keyValue, 1, strlen(keyValue), saveIniFile);
				
				if ((sections + 1) ==  m_SectionCount && (keys + 1) == m_ppIniSection[sections]->getkeyCount())
				{
				}else
				{
					fwrite("\n", 1, 1, saveIniFile);
				}
			}
		}
		fclose(saveIniFile);
	}

private:
IniSection** m_ppIniSection;
int m_SectionCount;
};



IniFile* loadIni(char* iniAddress);
void saveIni(IniFile* ini, char* iniAddress);

#endif
