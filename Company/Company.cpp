#include<windows.h>
#include<stdio.h>
#include"header.h"
#include"CompanyServerHeader.h"
#include<string.h>
#include<commctrl.h>		//comman control for listview

//id
#define ID_WRITE_BUTTON		401
#define ID_EDIT_NAME		402
#define ID_EDIT_ADDRESS		403
#define ID_EDIT_DEPT		404
#define ID_MALE_RADIO		405
#define ID_FEMALE_RADIO		406
#define ID_MOBILE			407
#define ID_READ_BUTTON		408
#define ID_LISTVIEW			409

IReadWrite *pIReadWrite = NULL;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcWrite(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcRead(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow) {

	HWND hwnd;
	TCHAR szAppName[255] = TEXT("Company");
	MSG msg;
	WNDCLASSEX wndclass;
	HRESULT hr;

	//init COM
	hr = CoInitialize(NULL);

	if (FAILED(hr)) {
		MessageBox(NULL,TEXT("Fail To Initialize COM"),TEXT("CoInitailize Failed"),MB_OK);
		exit(0);
	}


	//initialize wndclass

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;

	//register wndclassex class
	RegisterClassEx(&wndclass);

	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = TEXT("WRITE");
	wndclass.lpfnWndProc = WndProcWrite;

	//register wndclassex class for write
	RegisterClassEx(&wndclass);

	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndclass.lpszClassName = TEXT("READ");
	wndclass.lpfnWndProc = WndProcRead;

	//register wndclassex class for Read
	RegisterClassEx(&wndclass);


	//handle to the window
	hwnd = CreateWindow(szAppName,
		TEXT("Company- v0.0.1"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//show window
	ShowWindow(hwnd,SHOW_FULLSCREEN);
	UpdateWindow(hwnd);

	
	//messageloop
	while (GetMessage(&msg,NULL,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	CoUninitialize();
	return ((int)msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	HRESULT hr;

	static HBITMAP hBitmap = NULL;
	static BITMAP bmp;
	RECT rc;
	HDC hdc, hMemdc;
	static HWND hwndWrite;
	static HWND hwndRead;
	PAINTSTRUCT ps;
	static int flag = 0;
	//code
	switch (iMsg) {
	case WM_CREATE:

		hr = CoCreateInstance(CLSID_ReadWrite, NULL, CLSCTX_INPROC_SERVER, IID_IReadWrite, (void **)&pIReadWrite);

		if (FAILED(hr)) {
			MessageBox(NULL,TEXT("IReadWrite Interface Cannot Be Obtain"),TEXT("CoCreateInstance Failed"),MB_OK);
			DestroyWindow(hwnd);
		}

		hBitmap = (HBITMAP)LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(MYBITMAP));
		GetClientRect(hwnd, &rc);
		hwndWrite = CreateWindowEx(WS_EX_CLIENTEDGE,
			TEXT("WRITE"),
			TEXT("WRITE"),
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			0,
			0,
			rc.right / 2,
			rc.bottom,
			hwnd,
			NULL,
			(HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		hwndRead = CreateWindowEx(WS_EX_CLIENTEDGE,
			TEXT("READ"),
			TEXT("READ"),
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
			rc.right / 2 + 2,
			0,
			rc.right / 2,
			rc.bottom,
			hwnd,
			NULL,
			(HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance,
			NULL);


		//hide window initially
		ShowWindow(hwndWrite, SW_HIDE);
		ShowWindow(hwndRead, SW_HIDE);
		break;

	case WM_PAINT:

		if (flag == 0) {

			//client height
			GetClientRect(hwnd, &rc);
			//start the painting
			hdc = BeginPaint(hwnd, &ps);
			//DeviceContext
			hMemdc = CreateCompatibleDC(hdc);
			//Selecct object
			SelectObject(hMemdc, hBitmap);
			//get object
			GetObject(hBitmap, sizeof(bmp), &bmp);
			//Source to destination rectangle
			StretchBlt(hdc, 0, 0, rc.right, rc.bottom, hMemdc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
			//green
			//set background color
			SetBkColor(hdc, RGB(255, 255, 255));
			SetTextColor(hdc, RGB(255, 0, 0));
			TextOut(hdc, rc.right / 2 - 175, rc.bottom - 300, TEXT("~~  ROHIT SUDHIR KULKARNI  ~~"), strlen("~~  ROHIT SUDHIR KULKARNI  ~~"));
			SetTextColor(hdc, RGB(0, 255, 0));
			TextOut(hdc, rc.right / 2 - 175, rc.bottom - 300+35, TEXT("~~ ASTROMEDICOMP - WINRT2019  WM_HELP ~~"), strlen("~~ ASTROMEDICOMP - WINRT2019  WM_HELP ~~"));
			SetTextColor(hdc, RGB(0, 0, 255));
			TextOut(hdc, rc.right / 2 - 175, rc.bottom - 300+35+35, TEXT("Please Press Spacebar to continue..."), strlen("Please Press Spacebar to continue..."));
			//now no need of Object... delete the object
			SetBkColor(hdc, RGB(175, 175, 175));

			DeleteObject(hMemdc);
			//End Paint
			EndPaint(hwnd, &ps);
		}
		break;

	case WM_KEYDOWN:
		if (flag == 0) {
			flag = 1;
			InvalidateRect(hwnd, NULL, TRUE);
			ShowWindow(hwndWrite, SW_SHOW);
			ShowWindow(hwndRead, SW_SHOW);
		}

		break;

	case WM_SIZE:
		GetClientRect(hwnd, &rc);
		MoveWindow(hwndWrite, 0, 0, rc.right / 2, rc.bottom, TRUE);
		MoveWindow(hwndRead, rc.right/2, 0, rc.right / 2, rc.bottom, FALSE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

LRESULT CALLBACK WndProcWrite(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	static HWND hwndWriteButton = NULL;
	static HWND hwndEditName	= NULL;
	static HWND hwndEditAddress = NULL;
	static HWND hwndEditDept	= NULL;
	static HWND hwndMaleRadio	= NULL;
	static HWND hwndFemaleRadio = NULL;
	static HWND hwndMobile		= NULL;
	static HWND hwndReadButton = NULL;

	static int namelen = 0;
	static int deptlen = 0;
	static int addlen = 0;
	static int moblen = 0;
	static char* str = NULL;
	static int cxChar, cyChar;


	switch (iMsg) {
	case WM_CREATE:

		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());

		hwndWriteButton = CreateWindow(TEXT("button"),
			TEXT("Write"),
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			10,
			10,
			20*cxChar,
			7*cyChar /4,
			hwnd,
			(HMENU)ID_WRITE_BUTTON,((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		//________________NAME__________________________________________________
		CreateWindow(TEXT("static"),
			TEXT("NAME"),
			WS_CHILD | WS_VISIBLE | SS_CENTER,
			10,
			80,
			6 * cxChar,
			4 * cyChar / 4,
			hwnd,
			(HMENU)-1, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		hwndEditName =  CreateWindow(TEXT("EDIT"),
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER  | ES_LEFT ,
			(10 + 11 * cxChar) + 2,
			80,
			22 * cxChar,
			4 * cyChar / 4,
			hwnd,
			(HMENU)ID_EDIT_NAME, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

	//__________________ADDRESS_______________________________________________
		CreateWindow(TEXT("static"),
			TEXT("ADDRESS"),
			WS_CHILD | WS_VISIBLE | SS_CENTER,
			10,
			100,
			9 * cxChar,
			4 * cyChar / 4,
			hwnd,
			(HMENU)-1, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		hwndEditAddress = CreateWindow(TEXT("EDIT"),
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
			(10 + 11 * cxChar) + 2,
			100,
			22 * cxChar,
			4 * cyChar / 4,
			hwnd,
			(HMENU)ID_EDIT_ADDRESS, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		//_______________________________________________________________________________
		
	
		//__________________DEPARTMENT_______________________________________________
		CreateWindow(TEXT("static"),
			TEXT("DEPARTMNT"),
			WS_CHILD | WS_VISIBLE | SS_CENTER,
			10,
			122,
			11 * cxChar,
			4 * cyChar / 4,
			hwnd,
			(HMENU)-1, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		hwndEditDept = CreateWindow(TEXT("COMBOBOX"),
			NULL,
			CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
			(10 + 11 * cxChar) + 2,
			120,
			22 * cxChar,
			50 * cyChar / 4,
			hwnd,
			(HMENU)ID_EDIT_DEPT, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		SendMessage(hwndEditDept, CB_ADDSTRING, (WPARAM)0, (LPARAM)TEXT("IT"));
		SendMessage(hwndEditDept, CB_ADDSTRING, (WPARAM)0, (LPARAM)TEXT("Computer"));
		SendMessage(hwndEditDept, CB_ADDSTRING, (WPARAM)0, (LPARAM)TEXT("Finance"));
			
		SendMessage(hwndEditDept, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

		//______________________________________________________________________________________________

		//______________GENDER RADIO BUTTON ________________________________________________________________________________
		CreateWindow(TEXT("static"),
			TEXT("GENDER"),
			WS_CHILD | WS_VISIBLE | SS_CENTER,
			10,
			154,
			8 * cxChar,
			4 * cyChar / 4,
			hwnd,
			(HMENU)-1, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		hwndMaleRadio = CreateWindow(TEXT("button"),
			TEXT("MALE"),
			WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
			(10 + 11 * cxChar) + 2,
			150,
			10 * cxChar,
			7 * cyChar / 4,
			hwnd,
			(HMENU)ID_MALE_RADIO, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		SendMessage(hwndMaleRadio, BM_SETCHECK, (WPARAM)1, (LPARAM)0);
		ed.gender = (char*)"MALE";

	
		hwndFemaleRadio = CreateWindow(TEXT("button"),
			TEXT("FEMALE"),
			WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
			(10 + 11 * cxChar) + 10 * cxChar + 4,
			150,
			10 * cxChar,
			7 * cyChar / 4,
			hwnd,
			(HMENU)ID_FEMALE_RADIO, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		//__________________________________________________________________

		//___________MOBILE_______________________________________________________

		CreateWindow(TEXT("static"),
			TEXT("MOBILE"),
			WS_CHILD | WS_VISIBLE | SS_CENTER ,
			10,
			184,
			8 * cxChar,
			4 * cyChar / 4,
			hwnd,
			(HMENU)-1, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		
		hwndMobile = CreateWindow(TEXT("EDIT"),
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_NUMBER,
			(10 + 11 * cxChar) + 2,
			184,
			22 * cxChar,
			4 * cyChar / 4,
			hwnd,
			(HMENU)ID_MOBILE, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		break;

		case WM_COMMAND:
			
			if (LOWORD(wParam) == ID_WRITE_BUTTON) {

				//lenth of the string inside edit box
				namelen = GetWindowTextLength(hwndEditName);
				ed.name = (char *)malloc(sizeof(char) * (namelen + 1));
				SendMessage(hwndEditName, WM_GETTEXT, (WPARAM)namelen + 1, LPARAM(ed.name));

				addlen = GetWindowTextLength(hwndEditAddress);
				ed.address = (char *)malloc(sizeof(char) * (addlen + 1));
				SendMessage(hwndEditAddress, WM_GETTEXT, (WPARAM)addlen + 1, LPARAM(ed.address));
				

				deptlen = GetWindowTextLength(hwndEditDept);
				ed.dept = (char *)malloc(sizeof(char) * (deptlen + 1));
				SendMessage(hwndEditDept, WM_GETTEXT, (WPARAM)deptlen + 1, LPARAM(ed.dept));
			

				moblen = GetWindowTextLength(hwndMobile);
				SendMessage(hwndMobile, WM_GETTEXT, (WPARAM)moblen + 1, LPARAM(&ed.mobile));


				if ((namelen == 0) || (addlen == 0) || (moblen == 0)) {
					MessageBox(hwnd, TEXT("Please Fill All The Details"), TEXT("EMPTY FIELDS"), MB_OK | MB_ICONSTOP);
				}
				else {
					//Call WriteData of DLL
					pIReadWrite->WriteData(&ed);
					MessageBox(hwnd, TEXT("Data Succesfully Added"), TEXT("Complete !"), MB_OK | MB_ICONINFORMATION);
					free(ed.name);
					free(ed.address);
					free(ed.dept);

				}
				
			}
			else if((LOWORD(wParam) == ID_MALE_RADIO ) || (LOWORD(wParam) == ID_FEMALE_RADIO)) {

				if (LOWORD(wParam) == ID_MALE_RADIO) {
					
					SendMessage(hwndMaleRadio, BM_SETCHECK, (WPARAM)1, (LPARAM)0);
					SendMessage(hwndFemaleRadio, BM_SETCHECK, (WPARAM)0, (LPARAM)0);
					ed.gender = (char*)"MALE";
				

				}
				else if(LOWORD(wParam) == ID_FEMALE_RADIO) {

					SendMessage(hwndFemaleRadio, BM_SETCHECK, (WPARAM)1, (LPARAM)0);
					SendMessage(hwndMaleRadio, BM_SETCHECK, (WPARAM)0, (LPARAM)0);
					ed.gender = (char*)"FEMALE";
				
				}
			}
			
			
			break;
			
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

LRESULT CALLBACK WndProcRead(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	
	RECT rc;
	static HWND hListView = NULL; 
	static int cxChar, cyChar;
	static HWND hwndReadButton = NULL;

	switch (iMsg)
	{
	case WM_CREATE:
		InitCommonControls();

		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());

		GetClientRect(hwnd,&rc);


		hwndReadButton = CreateWindow(TEXT("button"),
			TEXT("Read"),
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			10,
			10,
			20 * cxChar,
			7 * cyChar / 4,
			hwnd,
			(HMENU)ID_READ_BUTTON, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);


		hListView = CreateWindow(WC_LISTVIEW,
			TEXT("List View"),
			WS_VISIBLE | WS_BORDER | WS_CHILD | LVS_REPORT ,
			10,
			100,
			rc.right - 10,
			rc.bottom - 50,
			hwnd,
			(HMENU)ID_LISTVIEW,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		ListView_SetExtendedListViewStyle(hListView, LVS_EX_GRIDLINES | LVS_EX_AUTOSIZECOLUMNS | LVS_EX_FULLROWSELECT);

		LVCOLUMN lvc;
		
		lvc.mask = LVCF_WIDTH | LVCF_WIDTH | LVCF_TEXT | LVCF_FMT | LVCF_SUBITEM;
		lvc.fmt = LVCFMT_LEFT;
		lvc.cx = ((rc.right - 10) - (rc.left + 10)) / 6;

		lvc.pszText = "Employee ID";
		lvc.iSubItem = 1;
		ListView_InsertColumn(hListView, 1, &lvc);

		lvc.pszText = "DEPARTMENT";
		lvc.iSubItem = 6;
		ListView_InsertColumn(hListView, 1, &lvc);

		lvc.pszText = "Mobile Number";
		lvc.iSubItem = 5;
		ListView_InsertColumn(hListView, 1, &lvc);
		
		lvc.pszText = "Gender";
		lvc.iSubItem = 4;
		ListView_InsertColumn(hListView, 1, &lvc);

		lvc.pszText = "Address";
		lvc.iSubItem = 3;
		ListView_InsertColumn(hListView, 1, &lvc);

		lvc.pszText = "Name";
		lvc.iSubItem = 2;
		ListView_InsertColumn(hListView, 1, &lvc);


		break;
	case WM_COMMAND:
	
		if (LOWORD(wParam) == ID_READ_BUTTON) {
			struct EmployeeData *data = NULL;
			char arr[10];

			//call ReadData of DLL
			pIReadWrite->ReadData(&data);
			//_______________________________________________
			
			SendMessage(hListView,LVM_DELETEALLITEMS,(WPARAM)0,(LPARAM)0);
			int ret;

			LVITEM lvi = { 0 };
			lvi.mask = LVIF_TEXT;
			lvi.iItem = 0;

			//_______________________________________________


			while (data != NULL) {
			
				itoa(data->e_id, arr, 10);
				lvi.pszText = arr;
				ret = ListView_InsertItem(hListView, &lvi);
				
				ListView_SetItemText(hListView, ret, 1, data->name);
			

				ListView_SetItemText(hListView, ret, 2, data->address);
				

				ListView_SetItemText(hListView, ret, 3, data->gender);
		

				ListView_SetItemText(hListView, ret, 4, data->mobile);
				

				ListView_SetItemText(hListView, ret, 5, data->dept);
			
		
				(lvi.iItem)++;

				data = data->nextdata;
			}

		}
		break;
	case WM_SIZE:
		
		GetClientRect(hwnd, &rc);
		MoveWindow(hListView, 10, 100, rc.right - 10, rc.bottom - 50,TRUE);

		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}