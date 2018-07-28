// ConsoleApplication2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "dllloader.h"


int main()
{
	FILE * pFile;
	size_t lSize;
	size_t result;
	/* ʹ������ָ������ڴ� */
	unique_ptr<MEM_LoadDllAPI> hDLL(GetMemLoadDllApp());
	unique_ptr<char> buffer;
	/* ��Ҫһ��byte��©�ض��������ļ���ֻ�ܲ��ö����Ʒ�ʽ�� */
	pFile = fopen("dlltest.dll", "rb");
	if (pFile == NULL)
	{
		fputs("File error", stderr);
		goto nPause;
	}
	/* ��ȡ�ļ���С */
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);
	/* �����ڴ�洢�����ļ� */
	buffer.reset(new char[(sizeof(char)*lSize)]);
	if (buffer == NULL)
	{
		fputs("Memory error", stderr);
		goto nPause;
	}
	/* ���ļ�������buffer�� */
	result = fread(&*buffer, 1, lSize, pFile);
	if (result != lSize)
	{
		fputs("Reading error", stderr);
		goto nPause;
	}
	/* ��ȡ�ɹ����ر��ļ��� */
	fclose(pFile);
	/* װ���ڴ浱�е�DLL�ļ� */
	hDLL->MemLoadLibrary(&*buffer, lSize);
	hDLL->MemFreeLibrary();
nPause:
	/* �ɹ�����ʧ�����ն��ᵽ��һ�� */
	system("pause");
    return 0;
}

