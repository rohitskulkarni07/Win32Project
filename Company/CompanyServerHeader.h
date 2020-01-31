#include<windows.h>

struct EmployeeData {
	int e_id;
	char* name;
	char* address;
	char* gender;
	char* dept;
	char mobile[10];

	struct EmployeeData *nextdata;
}ed;


class IReadWrite :public IUnknown {
public:
	virtual HRESULT __stdcall ReadData(struct EmployeeData **) = 0;
	virtual HRESULT __stdcall WriteData(struct EmployeeData *) = 0;
};
//	{C06840FA-8098-4E77-8DFE-414F499F5AED}
//	0xc06840fa, 0x8098, 0x4e77, 0x8d, 0xfe, 0x41, 0x4f, 0x49, 0x9f, 0x5a, 0xed

const CLSID CLSID_ReadWrite = { 0xc06840fa, 0x8098, 0x4e77, 0x8d, 0xfe, 0x41, 0x4f, 0x49, 0x9f, 0x5a, 0xed };

//	{93C1C042-C414-47D0-BE7C-75969402342F}
//	0x93c1c042, 0xc414, 0x47d0, 0xbe, 0x7c, 0x75, 0x96, 0x94, 0x2, 0x34, 0x2f

//
const IID IID_IReadWrite = { 0x93c1c042, 0xc414, 0x47d0, 0xbe, 0x7c, 0x75, 0x96, 0x94, 0x2, 0x34, 0x2f };


