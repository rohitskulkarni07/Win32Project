#include<Windows.h>
#include"CompanyServerHeader.h"
#include<stdio.h>
#include<string.h>

class CReadWrite :public IReadWrite {

private:
	long m_cRef;

public:
	CReadWrite(void);
	~CReadWrite(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall ReadData(struct EmployeeData **);
	HRESULT __stdcall WriteData(struct EmployeeData *);

};

class CReadWriteClassFactory :public IClassFactory {
private:
	long m_cRef;
public:
	CReadWriteClassFactory(void);
	~CReadWriteClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);


};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hInstance,DWORD dwReason,LPVOID lpReserved ) {
	
	switch (dwReason) {
	
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;

	}
	return(TRUE);

}

//_____________________________________________________________________________________________________________________
//_____________________________________________________________________________________________________________________

CReadWrite::CReadWrite(void) {
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);

}
CReadWrite::~CReadWrite(void) {
	InterlockedDecrement(&glNumberOfActiveComponents);
}
//_____________________________________________________________________________________________________________________
//_____________________________________________________________________________________________________________________

HRESULT CReadWrite::QueryInterface(REFIID riid, void **ppv) {
	if (riid == IID_IUnknown) {
		*ppv = static_cast<IReadWrite *>(this);
	}
	else if (riid == IID_IReadWrite) {
		*ppv = static_cast<IReadWrite *>(this);
	}
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}


ULONG CReadWrite::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CReadWrite::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(0);
}
//_____________________________________________________________________________________________________________________
//_____________________________________________________________________________________________________________________

HRESULT CReadWrite::ReadData(struct EmployeeData **info) {
	FILE *fp = NULL;
	fp = fopen("EmployeeInfo.dat", "r");
	
	if (fp == NULL) {
		MessageBox(NULL, TEXT("NO DATA TO READ"), TEXT("EMPTY FILE"), MB_OK | MB_ICONSTOP);
		return E_FAIL;
	}
	struct EmployeeData *temp = NULL;
	struct EmployeeData *tail = NULL;
	char filetemp[255];

	while (fscanf(fp,"%[^\n]%*c",filetemp)!=EOF) {
		temp = (struct EmployeeData *)malloc(sizeof(struct EmployeeData));
		
		temp->e_id = atoi(filetemp);
		
		fscanf(fp, "%[^\n]%*c", filetemp);
		temp->name = (char*)malloc(sizeof(char)*255);
		strcpy(temp->name, filetemp);

		fscanf(fp, "%[^\n]%*c", filetemp);
		temp->address = (char*)malloc(sizeof(char) * 255);
		strcpy(temp->address, filetemp);

		fscanf(fp, "%[^\n]%*c", filetemp);
		temp-> gender= (char*)malloc(sizeof(char) * 10);
		strcpy(temp->gender, filetemp);

		fscanf(fp, "%[^\n]%*c", filetemp);
		temp->dept = (char*)malloc(sizeof(char) * 255);
		strcpy(temp->dept, filetemp);

		fscanf(fp, "%[^\n]%*c", filetemp);
		strcpy(temp->mobile, filetemp);

		temp->nextdata = NULL;

		if (*info == NULL) {
			*info = tail = temp;
		}
		else {
			tail->nextdata = temp;
			tail = temp;
		}
	}




	return(S_OK);
}
HRESULT CReadWrite::WriteData(struct EmployeeData *info) {
	//code
	FILE *fp = NULL;
	FILE *fpeid = NULL;
	
	if (info == NULL) {
		MessageBox(NULL, TEXT("Info pointer is null"), TEXT("ERROR IN DLL"), MB_OK);
		return S_FALSE;
	}

	fp = fopen("EmployeeInfo.dat", "a");

	if (fp == NULL) {
		MessageBox(NULL, TEXT("File pointer is null"), TEXT("ERROR IN DLL"), MB_OK);
		return (-1);
	}

	fpeid = fopen("empid.dat", "r");
	if (fpeid == NULL) {
		MessageBox(NULL, TEXT("empid file pointer is null"), TEXT("ERROR IN DLL"), MB_OK);
		return (-1);
	}

	char eid[10];
	fgets(eid,10,fpeid);
	fclose(fpeid);
	//funtion atoi is to convert char array to int
	info->e_id = atoi(eid);

	fputs(eid, fp);
	fputs("\n", fp);

	itoa(info->e_id + 1, eid, 10);
	int len = strlen(eid);
	eid[len] = '\0';
	fpeid = fopen("empid.dat", "w");
	fputs(eid, fpeid);
	fclose(fpeid);

	fputs(info->name, fp);
	fputs("\n",fp);

	fputs(info->address,fp);
	fputs("\n", fp);

	fputs(info->gender,fp);
	fputs("\n", fp);

	fputs(info->dept, fp);
	fputs("\n", fp);

	fputs(info->mobile, fp);
	fputs("\n",fp);

	fclose(fp);
	return(S_OK);
}
//_____________________________________________________________________________________________________________________
//_____________________________________________________________________________________________________________________
//_____________________________________________________________________________________________________________________
//_____________________________________________________________________________________________________________________

CReadWriteClassFactory::CReadWriteClassFactory(void) {
	m_cRef = 1;
}
CReadWriteClassFactory::~CReadWriteClassFactory(void) {
	//blank
}
//_____________________________________________________________________________________________________________________
//_____________________________________________________________________________________________________________________

HRESULT CReadWriteClassFactory::QueryInterface(REFIID riid, void **ppv) {
	if (riid == IID_IUnknown) {
		*ppv = static_cast<IClassFactory *>(this);
	}
	else if (riid==IID_IClassFactory) {
		*ppv = static_cast<IClassFactory *>(this);
	}
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CReadWriteClassFactory::AddRef(void) {
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CReadWriteClassFactory::Release(void) {
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(0);
}
//_____________________________________________________________________________________________________________________
//_____________________________________________________________________________________________________________________

HRESULT CReadWriteClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv) {
	CReadWrite *pCReadWrite = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL) {
		return(CLASS_E_NOAGGREGATION);
	}

	pCReadWrite = new CReadWrite;
	if (pCReadWrite == NULL) {
		return(E_OUTOFMEMORY);
	}
	hr = pCReadWrite->QueryInterface(riid, ppv);
	pCReadWrite->Release();
	return(hr);

}
HRESULT CReadWriteClassFactory::LockServer(BOOL fLock) {
	if (fLock) {
		InterlockedIncrement(&glNumberOfActiveComponents);

	}
	else {
		InterlockedDecrement(&glNumberOfActiveComponents);
	}
	return(S_OK);
}
//_____________________________________________________________________________________________________________________
//_____________________________________________________________________________________________________________________

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv) {
	
	CReadWriteClassFactory *pCReadWriteClassFactory = NULL;
	HRESULT hr;
	FILE *fpeid = NULL;

	fpeid = fopen("empid.dat", "r");
	
	if (fpeid == NULL)  {
		fpeid = fopen("empid.dat","w");
		fputs("0", fpeid);
	}
	fclose(fpeid);
	   
	if (rclsid != CLSID_ReadWrite) {
		return(CLASS_E_CLASSNOTAVAILABLE);
	}
	
	pCReadWriteClassFactory = new CReadWriteClassFactory;
	if (pCReadWriteClassFactory == NULL) {
		return(E_OUTOFMEMORY);
	}

	hr = pCReadWriteClassFactory->QueryInterface(riid, ppv);
	pCReadWriteClassFactory->Release();
	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void) {

	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0)) {
		return(S_OK);
	}
	else {
		return(S_FALSE);
	}
}
//_____________________________________________________________________________________________________________________
//_____________________________________________________________________________________________________________________
//_____________________________________________________________________________________________________________________
//_____________________________________________________________________________________________________________________
//_____________________________________________________________________________________________________________________

