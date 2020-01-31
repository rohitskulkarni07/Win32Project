
ReadMe :	Win32 SDK Project 2019 Batch
		WM_HELP
		Rohit Sudhir Kulkarni
		https://github.com/rohitskulkarni07/Win32Project
			

Project Description :
		
			- The project includes form to fill the detail of the employee and view the record of the employee
			- This project created using Win32 API and COM class factory pattern
			- Project is divided in server and client part 
				-client > Frontend
				-server > backend funtionality of read, write.
			- The validation of details are before saving in file.
			
		
		
	Files Included in Project
	
		Codes
			1. Company.exe 			-> Company.abc
			2. CompanyServer.dll		-> CompanyServer.abc1
			3. CompanyServer.reg 		-> CompanyServer.abc2
			4. Company.rc			-> Company.abc3
			5  Company.res			-> Company.abc4
			6. CompanyServerHeader.h	-> CompanyServerHeader.abc5
			7. header.h			-> header.abc6
			8. CompanyServer.cpp		-> CompanyServer.abc7
			10. CompanyServer.def		-> CompanyServer.abc8

			
		ScreenShots
		
			1. RohitKulkarni_SplashScreen.jpg
			2. ReadWriteWindow.jpg
			3. validation1.jpg
			4. validation2.jpg
			4. WriteData.jpg
			5. ReadData.jpg			

	Project Navigation steps
		
		- Add CompanyServer.dll in Following Path : "C:/Windows/System32/"
		- double click on CompanyServer.reg file to register dll
		- start Application on double clicking it on Company.exe
		- *(In case Buiding this project on your pc... please refer "dll compile and link cmd.txt" and "exe compile and link cmd.txt"file for compilation and Linking)
		
		1. Company.exe
				- Run the .exe	RohitKulkarni_SplashScreen will display.

		2. Press Any Key To Start...
		
		3. ReadWrite Window Will Display On one Window within 2 section 
		
		3-a Section 1 conatain write buton on top left of first window
			fill the data
				Name:(text field)
				Address:(text field)
				Gender:(radio button)
				Department (Combo-box):
				Mobile:(text field accepts number only)

			click on write button data will be save in EmployeeInfo.dat file and *employee Id auto generated stored in empid.dat file
	
		3-b Section 2 that is second window contains Read Button on top left and listview for displaying record
			Click on read button it will display the record of employee
				display(listview):
				Employee id:
				Name:
				Address:
				Department:
				Gender:
				Mobile:
						
				
				
		4. All this process creates two Files in the Directory
			- User must view "EmployeeInfo.dat" for the person details in file.
			- This File displays all the entries done uptill Now.
			
		8. empid.dat
			- used for autogeneration of employee id
