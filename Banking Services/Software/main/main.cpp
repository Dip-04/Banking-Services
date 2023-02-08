#include <iostream>
#include <cstring>
#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <time.h>
#include "MMSystem.h"
#define SZ 30
FILE *ff, *fs, *fp, *fg;
using namespace std;
void Welcome(void);
void Frame(void);
void small_frame(void);
void Gotoxy(int, int);
void Play(int);
void flow(char *);
void del(void);
void rena(void);

class Bank
{
private:
	char fname[10], sname[10], pname[20], city[15], email[20], dob[15], atype, mob_no[10];
	char acno[7], pin[5], accno[7];
	int pcode;
	int day, mont, year, hour, mini, sec;
	float amt, bal, adl, prev;

public:
	void create(void);
	void help(void);
	void main_menu(void);
	void sub_menu(void);
	void admin(void);
	void note(void);
	void deposit(Bank);
	void fund_transfer(Bank);
	void change_pin(Bank);
	void other_services(Bank);
	void fast_cash(Bank);
	void cash_withdraw(Bank);
	void balance_enquiry(Bank);
	void mini_statement(Bank);
	Bank login_check(void);
};
class date
{
public:
	int aday, amonth, ayear, ahour, amin, asec;
	void date_times()
	{
		SYSTEMTIME t;
		GetLocalTime(&t);
		aday = t.wDay, amonth = t.wMonth, ayear = t.wYear, ahour = t.wHour, amin = t.wMinute, asec = t.wSecond;
	}
};
void Bank::sub_menu()
{
	system("cls");

	Bank r;
	r = login_check();
	fclose(fg);
	while (1)
	{

		int i;
		system("cls");
		system("COLOR 1F");
		Frame();
		Gotoxy(14, 15);
		cout << "1. CASH DEPOSIT";
		Gotoxy(14, 22);
		cout << "2. FUND TRANSFER";
		Gotoxy(14, 29);
		cout << "3. PIN CHANGE";
		Gotoxy(14, 36);
		cout << "4. OTHER SERVICES";

		Gotoxy(165, 15);
		cout << "5. FAST CASH";
		Gotoxy(165, 22);
		cout << "6. CASH WITHDRAWL";
		Gotoxy(165, 29);
		cout << "7. BALANCE ENQUIRY";
		Gotoxy(165, 36);
		cout << "8. MINI STATEMENT";
		Gotoxy(10, 45);
		cout << "E : Exit ";
		Gotoxy(85, 10);
		flow("SELECT YOUR TRANSACTION");
		Gotoxy(85, 11);
		flow("_______________________");

		int op;
		Gotoxy(90, 45);
		cout << " ";
		cin >> op;

		switch (op)
		{
		case 1:
		{
			deposit(r);
			break;
		}
		case 4:
		{
			other_services(r);
			break;
		}
		case 7:
		{
			balance_enquiry(r);
			break;
		}
		case 8:
		{
			mini_statement(r);
			break;
		}
		case 5:
		{
			fast_cash(r);
			break;
		}
		case 3:
		{
			change_pin(r);
			break;
		}
		case 2:
		{
			fund_transfer(r);
			break;
		}

		case 6:
		{
			cash_withdraw(r);
			break;
		}
		case '0':
		{
			main_menu();
			break;
		}

		default:
		{
			Gotoxy(64, 24);
			cout << "Invalid Input ";
			cout << "\a\a\a"; // terminating to mainmenu
			Sleep(1000);
			main_menu();
		}
		}
	}
}
void Bank::change_pin(Bank r) // argument object recieved from login_check function
{

	system("cls");
	Frame();

	FILE *fk, *fl;
	char npin1[5], npin2[5];
	Gotoxy(10, 19);
	cout << "YOUR PIN IS CONFIDENTIAL";
	Gotoxy(10, 21);
	cout << "NOBODY SHOULD SEE THE PIN";
	Gotoxy(10, 23);
	cout << "WHILE YOU ARE ENTERING IT.";
	Gotoxy(10, 25);
	cout << "MAKE YOUR PIN MORE SECURE BY";
	Gotoxy(10, 27);
	cout << "CHANGING IT FREQUENTLY.";
	Gotoxy(85, 15);
	cout << "ENTER NEW PIN : ";
	cin >> npin1;
	Gotoxy(85, 17);
	cout << "CONFIRM PIN   : ";
	cin >> npin2;
	Bank a;
	if (strcmp(npin1, npin2) == 0)
	{
		fk = fopen("E:\\cpp project\\Banking Services\\User Data\\accounts.txt", "r");
		fl = fopen("E:\\cpp project\\Banking Services\\User Data\\temp.txt", "w"); // finding current account details to accounts file for changing pin
		while (fscanf(fk, "%s %s %s %s %f \n", a.acno, a.pin, a.fname, a.sname, &a.amt) != EOF)
		{
			if (strcmp(r.acno, a.acno) == 0)
				strcpy(a.pin, npin1);
			fprintf(fl, "%s %s %s %s %f \n", a.acno, a.pin, a.fname, a.sname, a.amt);
		}
		fclose(fl);
		fclose(fk);
	}
	else
	{
		Gotoxy(85, 19);
		cout << "Password do not match try after some time \a\a\a";
		Sleep(1000);
		main_menu();
	}
	system("cls");
	small_frame();
	Gotoxy(85, 24);
	cout << "YOUR TRANSACTION IS BEING PROCESSED PLEASE WAIT";
	Sleep(1000);
	system("cls");
	small_frame();
	Gotoxy(85, 24);
	cout << "      TRANSACTION COMPLETED SUCCESSFULLY       \a\a";
	Sleep(1000);
	del(); // calling file delete function bottom section of the code
	main_menu();
}
void Bank::cash_withdraw(Bank r) // argument object recieved from login_check function
{
	FILE *f1, *f2, *f3; // declaring pointers in C style
	system("cls");
	int cash;
	Frame();
	Gotoxy(80, 15);
	cout << "PLEASE ENTER AMOUNT : ";
	cin >> cash;
	if (cash > r.amt)
	{
		system("cls");
		small_frame();
		Gotoxy(85, 24);
		cout << "WITHDRAWAL AMOUNT IS GREATER THAN THE AVAILABLE BALANCE \a\a\a";
		Sleep(1000);
		main_menu();
	}

	Bank g;
	g.prev = r.amt;
	g.amt = r.amt - cash; // present amount equals to amount sum of current transaction - prevs avilable balance
	strcpy(g.acno, r.acno);
	strcpy(g.fname, r.fname);
	strcpy(g.sname, r.sname);
	strcpy(g.pin, r.pin);
	g.adl = cash;

	date d;
	d.date_times();
	g.day = d.aday;
	g.mont = d.amonth;
	g.year = d.ayear;
	g.hour = d.ahour;
	g.mini = d.amin;
	g.sec = d.asec;
	// transacton APPENDING to transactions file
	Bank a;
	f1 = fopen("E:\\cpp project\\Banking Services\\User Data\\transactions.txt", "a");
	fprintf(f1, "%s %s %f %f %f %d %d %d %d %d %d \n", g.acno, g.fname, g.prev, g.adl, g.amt, g.day, g.mont, g.year, g.hour, g.mini, g.sec);
	fclose(f1);

	f2 = fopen("E:\\cpp project\\Banking Services\\User Data\\accounts.txt", "r"); // finding current account details to accounts file for changing amount
	f3 = fopen("E:\\cpp project\\Banking Services\\User Data\\temp.txt", "w");
	while (fscanf(f2, "%s %s %s %s %f \n", a.acno, a.pin, a.fname, a.sname, &a.amt) != EOF)
	{
		if (strcmp(g.acno, a.acno) == 0)
			a.amt = g.amt;
		fprintf(f3, "%s %s %s %s %f \n", a.acno, a.pin, a.fname, a.sname, a.amt);
	}
	fclose(f3);
	fclose(f2);

	system("cls");
	small_frame();
	Gotoxy(85, 24);
	cout << "AMOUNT WITHDRAWN  : " << g.adl << " FINAL BALANCE : " << g.amt;
	Sleep(3000);
	system("cls");
	small_frame();
	Gotoxy(85, 24);
	cout << "YOUR TRANSACTION IS BEING PROCESSED PLEASE WAIT ";
	Sleep(1000);
	system("cls");
	small_frame();
	Gotoxy(85, 24);
	cout << "       TRANSACTION COMPLETED SUCCESSFULLY       ";
	Sleep(100);
	Gotoxy(85, 26);
	Play(2);
	cout << "PLEASE COLLECT CASH \a\a";
	Sleep(1000);
	del(); // calling file delete function bottom section of the code
	main_menu();
	getch();
}
void Bank::fund_transfer(Bank r) // argument object recieved from login_check function
{
	system("cls");
	Frame();

	FILE *fk, *fl, *fm, *fn; // declaring pointers in C style
	char racno[7], rracno[7];
	int famt;
	Gotoxy(85, 21);
	cout << "ENTER RECEPIENT'S ACCOUNT NUMBER : ";
	cin >> racno;
	Gotoxy(85, 23);
	cout << "CONFIRM ACCOUNT NUMBER           : ";
	cin >> rracno;
	if (strcmpi(racno, rracno) == 0)
	{
	}
	else
	{
		system("cls");
		small_frame();
		Gotoxy(85, 25);
		cout << "GIVEN ACCOUNT NUMBER DOES NOT MATCH \a\a\a";
		Sleep(1000);
		main_menu();
	}
	system("cls");
	small_frame();
	Gotoxy(85, 24);
	cout << "PLEASE ENTER AMOUNT              : ";
	cin >> famt;
	if (famt > r.amt)
	{
		system("cls");
		small_frame();
		Gotoxy(85, 24);
		cout << "WITHDRAWAL AMOUNT IS GREATER THAN THE AVAILABLE BALANCE \a\a\a";
		Sleep(1000);
		main_menu();
	}

	Bank g;
	g.prev = r.amt;
	g.amt = r.amt - famt;
	g.adl = famt;
	strcpy(g.acno, r.acno);
	strcpy(g.fname, r.fname);
	strcpy(g.pin, r.pin);

	date d;
	d.date_times();
	g.day = d.aday;
	g.mont = d.amonth;
	g.year = d.ayear;
	g.hour = d.ahour;
	g.mini = d.amin;
	g.sec = d.asec;
	// transacton APPENDING to transactions file
	Bank a, b;
	fl = fopen("E:\\cpp project\\Banking Services\\User Data\\transactions.txt", "a");
	fprintf(fl, "%s %s %f %f %f %d %d %d %d %d %d \n", g.acno, g.fname, g.prev, g.adl, g.amt, g.day, g.mont, g.year, g.hour, g.mini, g.sec);
	fclose(fl);
	// finding current account details to accounts file for changing amount and also transfer account
	fm = fopen("E:\\cpp project\\Banking Services\\User Data\\accounts.txt", "r");
	fn = fopen("E:\\cpp project\\Banking Services\\User Data\\temp.txt", "w");
	while (fscanf(fm, "%s %s %s %s %f \n", a.acno, a.pin, a.fname, a.sname, &a.amt) != EOF)
	{
		if (strcmp(g.acno, a.acno) == 0) // transfer account
			a.amt = g.amt;

		else if (strcmp(racno, a.acno) == 0) // currnet account
		{

			b = a;
			b.prev = a.amt;
			b.amt = a.amt + famt;
			b.adl = famt; // transacton APPENDING to transactions file
			fk = fopen("E:\\cpp project\\Banking Services\\User Data\\transactions.txt", "a");
			fprintf(fk, "%s %s %f %f %f %d %d %d %d %d %d \n", b.acno, b.fname, b.prev, b.adl, b.amt, g.day, g.mont, g.year, g.hour, g.mini, g.sec);
			fclose(fk);

			a.amt = a.amt + famt;
		}

		fprintf(fn, "%s %s %s %s %f \n", a.acno, a.pin, a.fname, a.sname, a.amt);
	}
	fclose(fn);
	fclose(fm);
	system("cls");
	small_frame();
	Gotoxy(85, 24);
	cout << "AMOUNT TRANSFERRED : " << famt << " FINAL BALANCE : " << g.amt;
	Sleep(3000);
	system("cls");
	small_frame();
	Gotoxy(85, 24);
	cout << "YOUR TRANSACTION IS BEING PROCESSED PLEASE WAIT ";
	Sleep(1000);
	system("cls");
	small_frame();
	Gotoxy(85, 24);
	cout << "       TRANSACTION COMPLETED SUCCESSFULLY       \a\a";
	Sleep(1000);
	del(); // calling file delete function bottom section of the code
	main_menu();
	getch();
}

void Bank::mini_statement(Bank r) // argument object recieved from login_check function
{
	system("cls");
	FILE *fm; // declaring pointer in C style
	int l;
	system("COLOR E0");
	for (int i = 8; i < 40; i++)
	{
		Gotoxy(45, i);
		cout << "|";
		Gotoxy(170, i);
		cout << "|";
	}
	for (int i = 44; i < 171; i++)
	{
		Gotoxy(i, 7);
		cout << "_";
		Gotoxy(i, 5);
		cout << "_";
	}
	Gotoxy(146, 4);
	time_t t;
	time(&t);

	cout << ctime(&t);
	Gotoxy(50, 6);
	cout << "DATE           TIME          TRANSACTION TYPE            AMOUNT          FINAL BALANCE            ACCOUNT NUMBER	";
	Bank n; // checking account numer of current and to trasactions file
			// whenever it returns true it prints the transaction
	fm = fopen("E:\\cpp project\\Banking Services\\User Data\\transactions.txt", "r");
	l = 11;
	while (fscanf(fm, "%s %s %f %f %f %d %d %d %d %d %d \n", n.acno, n.fname, &n.prev, &n.adl, &n.amt, &n.day, &n.mont, &n.year, &n.hour, &n.mini, &n.sec) != EOF)
	{
		if (strcmp(r.acno, n.acno) == 0)
		{
			Gotoxy(50, l);
			if (n.amt > n.prev && n.prev != 0)
			{
				cout << setw(2) << n.day << "/" << setw(2) << n.mont << "/" << n.year << "    " << setw(2) << n.hour << ":" << setw(2) << n.mini << ":" << setw(2) << n.sec;
				cout << setw(18) << "   CASH DEPOSITED" << setw(15) << "  " << n.adl << setw(18) << "    " << n.amt << setw(21) << "    " << n.acno;
			}
			else if (n.amt < n.prev)
			{
				cout << setw(2) << n.day << "/" << setw(2) << n.mont << "/" << n.year << "    " << setw(2) << n.hour << ":" << setw(2) << n.mini << ":" << setw(2) << n.sec;
				cout << setw(19) << "   CASH WITHDRAWAL" << setw(14) << "  " << n.adl << setw(18) << "    " << n.amt << setw(21) << "    " << n.acno;
			}
			else if (n.amt > n.prev && n.prev == 0)
			{

				cout << setw(2) << n.day << "/" << setw(2) << n.mont << "/" << n.year << "    " << setw(2) << n.hour << ":" << setw(2) << n.mini << ":" << setw(2) << n.sec;
				cout << setw(19) << "   ACCOUNT OPENED" << setw(14) << "  " << n.adl << setw(18) << "    " << n.amt << setw(21) << "    " << n.acno;
			}
			l = l + 2;
		}
	}

	fclose(fm);
	getch();
	system("cls");
	small_frame();
	Gotoxy(85, 24);
	cout << "YOUR TRANSACTION IS BEING PROCESSED PLEASE WAIT";
	Sleep(1000);
	system("cls");
	small_frame();
	Gotoxy(85, 24);
	cout << "      TRANSACTION COMPLETED SUCCESSFULLY       \a\a";
	Play(4);
	Sleep(1000);
	main_menu();
}
void Bank ::balance_enquiry(Bank r) // argument object recieved from login_check function
{
	system("cls");
	small_frame();
	Gotoxy(90, 22);
	cout << "ACCOUNT HOLDER NAME  : " << r.fname;
	Gotoxy(90, 24);
	cout << "CURRENT BALANCE      : " << r.amt;
	Sleep(3000);
	system("cls");
	small_frame();
	Gotoxy(85, 24);
	cout << "YOUR TRANSACTION IS BEING PROCESSED PLEASE WAIT ";
	Sleep(1000);
	system("cls");
	small_frame();
	Gotoxy(85, 24);
	cout << "       TRANSACTION COMPLETED SUCCESSFULLY       \a\a";
	Play(4);
	Sleep(1000);
	main_menu();
}

void Bank::deposit(Bank r) // argument object recieved from login_check function
{
	FILE *f1, *f2, *f3; // declaring pointers in C style
	system("cls");
	int cash;
	Frame();
	Gotoxy(80, 15);
	cout << "PLEASE ENTER AMOUNT : ";
	Gotoxy(102, 15);
	cin >> cash;
	Bank g;
	g.prev = r.amt;		  // holding available balance before transaction which equals to present previous amount
	g.amt = r.amt + cash; // present amount equals to amount sum of current transaction + prevs avilable balance
	strcpy(g.acno, r.acno);
	strcpy(g.fname, r.fname);
	strcpy(g.sname, r.sname);
	strcpy(g.pin, r.pin);
	g.adl = cash; // additional amount will be currents transaction amount

	date d;
	d.date_times();
	g.day = d.aday;
	g.mont = d.amonth;
	g.year = d.ayear;
	g.hour = d.ahour;
	g.mini = d.amin;
	g.sec = d.asec;

	// transacton APPENDING to transactions file
	Bank a;
	f1 = fopen("E:\\cpp project\\Banking Services\\User Data\\transactions.txt", "a");
	fprintf(f1, "%s %s %f %f %f %d %d %d %d %d %d \n", g.acno, g.fname, g.prev, g.adl, g.amt, g.day, g.mont, g.year, g.hour, g.mini, g.sec);
	fclose(f1);

	f2 = fopen("E:\\cpp project\\Banking Services\\User Data\\accounts.txt", "r"); // finding current account details to accounts file for changing amount
	f3 = fopen("E:\\cpp project\\Banking Services\\User Data\\temp.txt", "w");
	while (fscanf(f2, "%s %s %s %s %f\n", a.acno, a.pin, a.fname, a.sname, &a.amt) != EOF)
	{
		if (strcmp(g.acno, a.acno) == 0)
			a.amt = g.amt;
		fprintf(f3, "%s %s %s %s %f \n", a.acno, a.pin, a.fname, a.sname, a.amt);
	}
	fclose(f3);
	fclose(f2);

	system("cls");
	small_frame();
	Gotoxy(80, 22);
	cout << "AMOUNT DEPOSITED  : " << g.adl << " FINAL BALANCE : " << g.amt;
	Sleep(2000);
	system("cls");
	small_frame();
	Gotoxy(80, 22);
	cout << "	      PLEASE WAIT VALIDATING THE CASH		";
	Sleep(1000);
	system("cls");
	small_frame();
	Gotoxy(80, 22);
	cout << "       TRANSACTION COMPLETED SUCCESSFULLY       \a\a";
	Play(4);
	Sleep(1000);
	del(); // calling file delete function bottom section of the code
	main_menu();
}
void Bank::other_services(Bank r) // argument object recieved from login_check function
{
	system("cls");
	system("COLOR 70");
	small_frame();

	Gotoxy(55, 9);
	cout << "Good to see here ";
	Gotoxy(143, 9);
	cout << "Mr." << strupr(r.fname) << "_" << strupr(r.sname); // name of user on top right
	Gotoxy(100, 12);
	cout << "POINTS TO NOTE";
	Gotoxy(55, 15);

	cout << "Ensure that you change the PIN number after first using your card also";
	Gotoxy(55, 16);
	cout << ("frequently change PIN number");
	Gotoxy(55, 18);
	cout << "Ensure that nobody else can see you entering your PIN number at the ATM.";
	Gotoxy(55, 20);
	cout << "Do not use the ATM Bank when strangers are inside the ATM counter.";
	Gotoxy(55, 22);
	cout << "Do not seek the assistance of strangers while operating the ATM Bank.	";
	Gotoxy(55, 24);
	cout << "Should you notice anything strange or suspicious at the ATM counter please";
	Gotoxy(55, 25);
	cout << "refrain from using  the same.";
	Gotoxy(55, 27);
	cout << "Ensure that you check your account statement from time to time.";
	Gotoxy(55, 29);
	cout << "In case you lose your ATM card call 1800-425-3800 to block your card and ";
	Gotoxy(55, 30);
	cout << "this avoid misuse of the card.";
	Gotoxy(55, 33);
	cout << "Do not disclose your PIN number to others IBO/RBI or any other Government,";
	Gotoxy(55, 34);
	cout << "Banking institutions will never require you to disclose your PIN number.";
	Play(3);
	Gotoxy(85, 37);
	flow("-------------------------------");
	Gotoxy(85, 39);
	flow("--------------------------------");
	Gotoxy(97, 38);
	cout << " THANK YOU ";
	Sleep(1000);
	Gotoxy(78, 24);
	cout << "";
	system("cls");
	system("color 2F");
	Gotoxy(80, 22);
	cout << "       TRANSACTION COMPLETED SUCCESSFULLY       \a\a";
	Sleep(1000);
	main_menu();
}

void del()
{
	char ac[] = "E:\\cpp project\\Banking Services\\User Data\\accounts.txt";
	int aaa;
	// system function (remove) in stdio.h header
	aaa = remove(ac);
	cout << "\n\ndel " << aaa;
	rena();
}
void rena()
{
	char acc[] = "E:\\cpp project\\Banking Services\\User Data\\accounts.txt";
	char tmp[] = "E:\\cpp project\\Banking Services\\User Data\\temp.txt";
	int bbc;
	// system function (rename) in stdio.h header
	bbc = rename(tmp, acc);
	cout << " ren" << bbc;
}

void Bank::main_menu()
{
	system("cls");
	system("COLOR 2F");
	Frame();
	Gotoxy(85, 21);
	cout << "CREATE ACCOUNT";
	Gotoxy(85, 25);
	cout << "ALREADY HAVE ACCOUNT PRESS P TO PROCEED ";
	Gotoxy(178, 38);
	cout << "HELP";
	char op;
	Gotoxy(10, 42);
	cout << "C : Create account ";

	Gotoxy(10, 43);
	cout << "P : Proceed to account ";
	Gotoxy(10, 44);
	cout << "H : Help ";
	Gotoxy(10, 6);
	cout << "ADMIN ";
	Gotoxy(10, 45);
	cout << "E : Exit ";
	Gotoxy(35, 43);
	cout << "";
	op = getch();

	if (op == 'c' || op == 'C')
	{
		create();
	}
	else if (op == 'p' || op == 'P')
	{
		system("cls");
		sub_menu();
	}
	else if (op == 'h' || op == 'H')
	{
		system("cls");
		help();
	}
	else if (op == 'a' || op == 'A')
	{
		system("cls");
		admin();
	}
	else if (op == 'e' || op == 'E')
	{
		system("cls");
		note();
	}
	else
	{
		cout << " \a\a\aINVALID OPTION ";
		Sleep(1000);
		main_menu();
	}
}
void Bank ::admin()
{
	char addname[15], pass[8];
	char adname[] = "Diptish";
	char password[] = "2213535";
	int z = 13;
	system("cls");
	system("cls");
	system("COLOR 1F");
	Frame();
	Gotoxy(88, 11);
	cout << "ADMIN LOGIN";
	Gotoxy(88, 12);
	cout << "____________";
	Gotoxy(85, 21);
	cout << "Enter Username : ";
	Gotoxy(102, 21);
	cin >> addname;
	if (strcmpi(adname, addname) == 0)
	{
		Gotoxy(85, 24);
		cout << "Enter Password : ";
		Gotoxy(102, 24);
		cin >> pass;
		if (strcmpi(password, pass) == 0)
		{
			while (1)
			{

				system("cls");
				small_frame();
				system("color 02");
				int op;
				Gotoxy(90, 20);
				cout << "1. ACCOUNT MEMBERS ";
				Gotoxy(90, 23);
				cout << "2. ACCOUNT TRANSACTIONS ";
				Gotoxy(90, 26);
				cout << "3. MAIN MENU ";
				Gotoxy(90, 29);
				cout << "Select : ";
				cin >> op;

				if (op == 1)
				{
					system("cls");
					Frame();
					FILE *fy;
					Bank b;
					int i = 3;
					fy = fopen("E:\\cpp project\\Banking Services\\User Data\\accounts.txt", "r"); // all information from accounts file
					Gotoxy(60, 10);
					cout << "ACCOUNT NUMBER		PIN NUMBER	     FULL NAME	         AVAILABLE BALANCE";
					while (fscanf(fy, "%s %s %s %s %f \n", b.acno, b.pin, b.fname, b.sname, &b.amt) != EOF)
					{

						Gotoxy(60, z);
						cout << b.acno << "		           " << b.pin << "		 " << b.fname << " " << b.sname << "	         " << b.amt;
						z = z + 2;
					}
					fclose(fy);
					getch();
				}
				else if (op == 2)
				{
					system("cls");
					Frame();
					FILE *fz;
					Bank z;
					int l;
					Gotoxy(60, 10);
					cout << "DATE         TIME          TRANSACTION TYPE            AMOUNT          FINAL BALANCE            ACCOUNT NUMBER	";

					fz = fopen("E:\\cpp project\\Banking Services\\User Data\\transactions.txt", "r"); // all information from transactions file
					l = 13;
					while (fscanf(fz, "%s %s %f %f %f %d %d %d %d %d %d \n", z.acno, z.fname, &z.prev, &z.adl, &z.amt, &z.day, &z.mont, &z.year, &z.hour, &z.mini, &z.sec) != EOF)
					{
						Gotoxy(60, l);
						if (z.amt > z.prev && z.prev != 0)
						{
							cout << setw(2) << z.day << "/" << setw(2) << z.mont << "/" << z.year << "    " << setw(2) << z.hour << ":" << setw(2) << z.mini << ":" << setw(2) << z.sec;
							cout << setw(18) << "   CASH DEPOSITED" << setw(15) << "  " << z.adl << setw(18) << "    " << z.amt << setw(21) << "    " << z.acno;
						}
						else if (z.amt < z.prev)
						{
							cout << setw(2) << z.day << "/" << setw(2) << z.mont << "/" << z.year << "    " << setw(2) << z.hour << ":" << setw(2) << z.mini << ":" << setw(2) << z.sec;
							cout << setw(19) << "   CASH WITHDRAWAL" << setw(14) << "  " << z.adl << setw(18) << "    " << z.amt << setw(21) << "    " << z.acno;
						}
						else if (z.amt > z.prev && z.prev == 0)
						{
							cout << setw(2) << z.day << "/" << setw(2) << z.mont << "/" << z.year << "    " << setw(2) << z.hour << ":" << setw(2) << z.mini << ":" << setw(2) << z.sec;
							cout << setw(18) << "   ACCOUNT OPENED" << setw(15) << "  " << z.adl << setw(18) << z.amt << setw(21) << "    " << z.acno;
						}
						l = l + 2;
					}

					fclose(fz);
					getch();
				}
				else
				{
					system("cls");
					Gotoxy(35, 13);
					cout << "INVALID OPTION \a\a\a";
					main_menu();
				}
			}
		}
		else
		{
			system("cls");
			Gotoxy(25, 17);
			cout << "INVALID USERNAME OR PASSWORD \a\a\a";
			getch();
			main_menu();
		}
	}
}
void flow(char *ch) // flow of instructions
{
	char *str = ch;
	for (int i = 0; i < strlen(str); i++)
	{
		Sleep(20);
		cout << str[i];
	}
}
void Bank::help() // initial help notice in mainmenu on opening account
{
	system("cls");
	system("COLOR 70");
	small_frame();
	Gotoxy(80, 11);
	cout << "Inorder to use our Banking services be sure that,";
	Gotoxy(80, 13);
	cout << "you might have already opened an account previously. ";

	Gotoxy(56, 42);
	cout << "For more information, contact:";
	Gotoxy(56, 43);
	cout << "Call our 24x7 helpline through toll free 1800 30000 123.";
	Gotoxy(56, 44);
	cout << "Contact at diptishgohane04@gmail.com";

	Gotoxy(56, 18);
	flow("ATM Services");
	Gotoxy(56, 21);
	flow("Cash Withdrawal : Use this service to withdraw amount (40,000/-per day).");
	Gotoxy(56, 24);
	flow("Fast Cash : This enables to withdraw your preferred amounts with a touch.");
	Gotoxy(56, 27);
	flow("Pin Change : Use this service to change your ATM password.");
	Gotoxy(56, 30);
	flow("Balance Enquiry : To check the current balance in your account.");
	Gotoxy(56, 33);
	flow("Mini statement : Keep track of the transactions in your account.");
	Gotoxy(56, 36);
	flow("Fund Transfer : Transfers amount instantly to your loved ones.");

	getch();
	main_menu();
}
Bank Bank::login_check()
{
	system("cls");
	system("COLOR 1F");
	Frame();

	int cnt, e = 0;
	char x, y;
	char apin[3] = {0}, aacno[7] = {0};
	char p1, p2, p3, p4;
	p1 = p2 = p3 = p4 = 0;
	char ans;
y:
	Gotoxy(85, 21);
	cout << " PLEASE ENTER YOUR ACCOUNT NUMBER ";
	Gotoxy(87, 23);
	cin >> aacno;
	system("cls");
	Frame();
	Gotoxy(85, 7);
	cout << "DIPTISH BANK SERVICES";
	Gotoxy(61, 7);
	cout << "                        ";

	Gotoxy(85, 15);
	cout << "PLEASE ENTER YOUR PIN";

	Gotoxy(10, 19);
	cout << "YOUR PIN IS CONFIDENTIAL";
	Gotoxy(10, 21);
	cout << "NOBODY SHOULD SEE THE PIN";
	Gotoxy(10, 23);
	cout << "WHILE YOU ARE ENTERING IT.";
	Gotoxy(10, 25);
	cout << "MAKE YOUR PIN MORE SECURE BY";
	Gotoxy(10, 27);
	cout << "CHANGING IT FREQUENTLY.";
	Gotoxy(90, 18);
	apin[0] = getche();
	Gotoxy(90, 18);
	cout << "        ";
	Gotoxy(90, 18);
	cout << "X"
		 << "\a";
	Gotoxy(91, 18);

	apin[1] = getche();
	Gotoxy(91, 18);
	cout << "       ";
	Gotoxy(91, 18);
	cout << "X"
		 << "\a";
	Gotoxy(92, 18);

	apin[2] = getche();
	Gotoxy(92, 18);
	cout << "        ";
	Gotoxy(92, 18);
	cout << "X"
		 << "\a";
	Gotoxy(93, 18);

	apin[3] = getche();
	Gotoxy(93, 18);
	cout << "        ";
	Gotoxy(93, 18);
	cout << "X"
		 << "\a";

	fg = fopen("E:\\cpp project\\Banking Services\\User Data\\accounts.txt", "rb+");
	Bank b, q;
	while (fscanf(fg, "%s %s %s %s %f \n", b.acno, b.pin, b.fname, b.sname, &b.amt) != EOF)
	{
		if ((strcmpi(aacno, b.acno) == 0) && (strcmpi(apin, b.pin) == 0))
		{
			q = b;

			system("cls");
			Frame();
			Gotoxy(93, 18);

			cout << "HELLO__MR. " << strupr(b.fname);
			Sleep(1000);
			return q;
		}
	}

	fclose(fg);
}

void Bank::create()
{
	Bank a;

	system("cls");
	system("COLOR F5");

	for (int i = 5; i < 45; i++)
	{
		Gotoxy(10, i);
		cout << "|";
		Gotoxy(175, i);
		cout << "|";
	}
	Gotoxy(85, 2);
	cout << "APPLICATION FORM";
	Gotoxy(85, 3);
	cout << "_________________";
	Gotoxy(20, 10);
	cout << "Enter Full Name : ";
	cin >> a.fname >> a.sname;
	Gotoxy(20, 12);
	cout << "Father/Guardian : ";
	cin >> a.pname;
	Gotoxy(20, 14);
	cout << "Date Of Birth (dd/mm/yyyy) : ";
	cin >> a.dob;
	Gotoxy(20, 16);
	cout << "Account Type (S/C): ";
	cin >> a.atype;
	Gotoxy(20, 18);
	cout << "City : ";
	cin >> a.city;
	Gotoxy(20, 20);
	cout << "PINCODE : ";
	cin >> a.pcode;
	Gotoxy(20, 22);
	cout << "Email Id : ";
	cin >> a.email;
	Gotoxy(20, 24);
	cout << "Mobile no : ";
	cin >> a.mob_no;
	Gotoxy(20, 26);
e:
	cout << "Enter initial amount( >= 500) ";
	cin >> a.amt;
	if (a.amt < 500)
	{
		Gotoxy(20, 28);
		cout << "ERROR!!!! INITAL AMOUNT >=500";
		goto e;
	}
// a.bal=a.amt;
// a.amt=0;
x:
	Gotoxy(20, 30);
	Bank b;
	cout << "SET ACCOUNT NO.(THIS IS TEMPORARY) : ";
	cin >> a.acno;
	Gotoxy(20, 32);
	cout << "SET PIN : ";
	cin >> a.pin;
	/*char ci=_getch();
	while(ci!= 13)
	{
		a.pin.push_back(ci);
		cout<<'x';
		ci=_getch();

	}*/

	fs = fopen("E:\\cpp project\\Banking Services\\User Data\\accounts.txt", "rb+");
	// initially there must be a valid user who have created account already
	// so that on using his account information, card details are given for next
	// for initail account there must be a file with his deatails

	while (fscanf(fs, "%s %s %s %s %f \n", b.acno, b.pin, b.fname, b.sname, &b.amt) != EOF)
		;
	strcpy(b.acno, a.acno);
	if (a.acno[5] != '9')
		a.acno[5] = a.acno[5] + 1;
	else
	{
		if (a.acno[4] != '9') // incrementing the account number..actualyy thought of creating a random one but involves some complexity
		{					  // but you can try it
			a.acno[4] = a.acno[4] + 1;
			a.acno[5] = '0';
		}
	}
	fprintf(fs, "%s %s %s %s %f \n", a.acno, a.pin, a.fname, a.sname, a.amt);
	fclose(fs);

	// inital account details posting to atm_users file
	ff = fopen("E:\\cpp project\\Banking Services\\User Data\\atm_users.txt", "a");
	fprintf(ff, "%s %s %s%s %s %s %c %s %d %s %s %f \n", a.acno, a.pin, a.fname, a.sname, a.pname, a.dob, a.atype, a.city, a.pcode, a.email, a.mob_no, a.amt);
	fclose(ff);

	// initialize amount,time & date of account opened and APPENDING to transactions file
	a.adl = a.amt; // adl = additional amount either deposit/credit
	a.prev = 0;	   // prev = available balance before transaction
	date d;
	d.date_times();
	a.day = d.aday;
	a.mont = d.amonth;
	a.year = d.ayear;
	a.hour = d.ahour;
	a.mini = d.amin;
	a.sec = d.asec;
	// to transactions file
	fp = fopen("E:\\cpp project\\Banking Services\\User Data\\transactions.txt", "a");
	fprintf(fp, "%s %s %f %f %f %d %d %d %d %d %d \n", a.acno, a.fname, a.prev, a.adl, a.amt, a.day, a.mont, a.year, a.hour, a.mini, a.sec);
	fclose(fp);

	Gotoxy(50, 36);
	cout << " SUBMIT";
	char ch;
	ch = getche();

	system("cls");
	Frame();
	Gotoxy(85, 25);
	cout << "Loading";
	Sleep(400);
	cout << ".";
	Sleep(400);
	cout << ".";
	Sleep(400);
	cout << ".";
	Sleep(400);

	system("cls");
	system("COLOR B0");
	Frame();
	Gotoxy(85, 10);
	cout << "YOUR ACCOUNT HAS SUCCESSFULLY CREATED ";
	Gotoxy(90, 25); // giving account deatails on that particular user
	cout << "ACCOUNT NUMBER  : " << a.acno;
	Gotoxy(90, 26);
	cout << "ATM PIN	  : " << a.pin;
	Gotoxy(80, 39);
	cout << "NOTE : THESE ARE THE ACCOUNT CREDENTIALS FOR USING ATM SERVICES.";
	Gotoxy(90, 41);
	cout << "MAIN MENU : PRESS ENTER";
	char op;
	op = getche();
	main_menu();
}

void Bank::note()
{
	system("cls");
	system("color F0");
	int i, j, k, l;

	for (k = 135; k >= 75; k--)
	{

		Gotoxy(k, 10);
		cout << "_";
		Gotoxy(k, 33);
		cout << "_";
	}
	for (l = 11; l < 34; l++)
	{

		Gotoxy(75, l);
		cout << "|\n";
		Gotoxy(135, l);
		cout << "|\n";
	}
	Gotoxy(80, 15);
	cout << "HELLO FRIENDS GOOD TO SEE YOU HERE ";
	Gotoxy(80, 17);
	cout << "THIS IS THE PROJECT DONE FOR 1ND YEAR 2ND SEM .";
	Gotoxy(80, 19);
	cout << "I HOPE IT IS SIMPLE AND EASY TO UNDERSTAND.";
	Gotoxy(80, 21);
	cout << "THE PROJECT HAVE BEEN CODED  IN C++.";
	Gotoxy(80, 23);
	cout << "AND I AM IN PROGRESS  ON OUR COMING SEMISTER PROJECT.";
	Gotoxy(80, 25);
	cout << "AND YOU CAN ALSO MAKE CHANGES FOR MORE EFFICIENT.";
	Gotoxy(80, 29);

	cout << "THANKS ";
	Gotoxy(80, 30);
	cout << "CONTACT AT : DIPTISHGOHANE04@GMAIL.COM";

	Gotoxy(120, 35);
	cout << "MIT-ADT PUNE.\n";

	system("pause");
	Play(4);
	exit(0);
}
void Frame()
{
	int i, j;
	for (i = 10; i < 185; i++)
	{
		Gotoxy(i, 8);

		cout << "_";
		Gotoxy(i, 40);

		cout << "_";
	}
	Gotoxy(160, 6);
	time_t t;
	time(&t);

	cout << ctime(&t);
}
void small_frame()
{
	int i, j;
	for (i = 53; i < 160; i++)
	{
		Gotoxy(i, 8);

		cout << "_";
		Gotoxy(i, 40);

		cout << "_";
	}
	Gotoxy(135, 6);
	time_t t;
	time(&t);
	cout << ctime(&t);
	for (int i = 9; i < 41; i++)
	{
		Gotoxy(53, i);
		cout << "|";
		Gotoxy(160, i);
		cout << "|";
	}
}
void Bank::fast_cash(Bank r) // argument object recieved from login_check function
{

	FILE *fr, *fs, *ft; // declaring pointers in C style
	system("cls");
	Frame();
	int choice;
	Bank g;
	g.prev = r.amt;
	strcpy(g.acno, r.acno);
	strcpy(g.fname, r.fname);
	strcpy(g.sname, r.sname);
	strcpy(g.pin, r.pin);
	Gotoxy(85, 10);
	flow("SELECT YOUR TRANSACTION AMOUNT");
	Gotoxy(14, 15);
	cout << "1. 100";
	Gotoxy(14, 22);
	cout << "2. 500";
	Gotoxy(14, 29);
	cout << "3. 1000";
	Gotoxy(165, 15);
	cout << "4. 1500";
	Gotoxy(165, 22);
	cout << "5. 2500";
	Gotoxy(165, 29);
	cout << "6. 5000 ";
	Gotoxy(90, 45);
	cout << "";
	cin >> choice;
	switch (choice)
	{
	case 1:
		g.adl = 100;

		if (g.adl > r.amt)
		{
			system("cls");
			small_frame();
			Gotoxy(80, 22);
			cout << "WITHDRAWAL AMOUNT IS GREATER THAN THE AVAILABLE BALANCE \a\a\a";
			Sleep(1000);
			main_menu();
		}
		g.amt = r.amt - 100;
		break;
	case 2:
		g.adl = 500;
		if (g.adl > r.amt)
		{
			system("cls");
			small_frame();
			Gotoxy(80, 22);
			cout << "WITHDRAWAL AMOUNT IS GREATER THAN THE AVAILABLE BALANCE \a\a\a";
			Sleep(1000);
			main_menu();
		}
		g.amt = r.amt - 500;
		break;
	case 3:
		g.adl = 1000;
		if (g.adl > r.amt)
		{
			system("cls");
			small_frame();
			Gotoxy(80, 22);
			cout << "WITHDRAWAL AMOUNT IS GREATER THAN THE AVAILABLE BALANCE \a\a\a";
			Sleep(1000);
			main_menu();
		}
		g.amt = r.amt - 1000;
		break;
	case 4:

		g.adl = 1500;
		if (g.adl > r.amt)
		{
			system("cls");
			small_frame();
			Gotoxy(80, 22);
			cout << "WITHDRAWAL AMOUNT IS GREATER THAN THE AVAILABLE BALANCE \a\a\a";
			Sleep(1000);
			main_menu();
		}
		g.amt = r.amt - 1500;
		break;
	case 5:
		g.adl = 2500;
		if (g.adl > r.amt)
		{
			system("cls");
			small_frame();
			Gotoxy(80, 22);
			cout << "WITHDRAWAL AMOUNT IS GREATER THAN THE AVAILABLE BALANCE \a\a\a";
			Sleep(1000);
			main_menu();
		}
		g.amt = r.amt - 2500;
		break;
	case 6:
		g.adl = 5000;
		if (g.adl > r.amt)
		{
			system("cls");
			small_frame();
			Gotoxy(80, 22);
			cout << "WITHDRAWAL AMOUNT IS GREATER THAN THE AVAILABLE BALANCE \a\a\a";
			Sleep(1000);
			main_menu();
		}
		g.amt = r.amt - 5000;
		break;
	default:
		cout << "INVALID OPTION \a\a\a";
		Sleep(1000);
		main_menu();
	}

	date d;
	d.date_times();
	g.day = d.aday;
	g.mont = d.amonth;
	g.year = d.ayear;
	g.hour = d.ahour;
	g.mini = d.amin;
	g.sec = d.asec;
	// transacton APPENDING to transactions file
	Bank a;
	fr = fopen("E:\\cpp project\\Banking Services\\User Data\\transactions.txt", "a");
	fprintf(fr, "%s %s %f %f %f %d %d %d %d %d %d \n", g.acno, g.fname, g.prev, g.adl, g.amt, g.day, g.mont, g.year, g.hour, g.mini, g.sec);
	fclose(fr);

	fs = fopen("E:\\cpp project\\Banking Services\\User Data\\accounts.txt", "r");
	ft = fopen("E:\\cpp project\\Banking Services\\User Data\\temp.txt", "w"); // finding current account details to accounts file for changing amount
	while (fscanf(fs, "%s %s %s %s %f \n", a.acno, a.pin, a.fname, a.sname, &a.amt) != EOF)
	{
		if (strcmp(g.acno, a.acno) == 0)
			a.amt = g.amt;
		fprintf(ft, "%s %s %s %s %f \n", a.acno, a.pin, a.fname, a.sname, a.amt);
	}
	fclose(ft);
	fclose(fs);

	system("cls");
	small_frame();
	Gotoxy(80, 22);
	cout << "AMOUNT WITHDRAWN : " << g.adl << " FINAL BALANCE : " << g.amt;
	Sleep(3000);
	system("cls");
	small_frame();
	Gotoxy(80, 22);
	cout << "YOUR TRANSACTION IS BEING PROCESSED PLEASE WAIT ";
	Sleep(1000);
	system("cls");
	small_frame();
	Gotoxy(80, 22);
	cout << "       TRANSACTION COMPLETED SUCCESSFULLY       ";
	system("cls");
	small_frame();
	Gotoxy(80, 22);
	Play(2);
	cout << "PLEASE COLLECT CASH \a\a";
	Sleep(1000);
	del(); // calling file delete function bottom section of the code
	main_menu();
	getch();
}

void Play(int a)
{

	if (a == 1)
		PlaySound(TEXT("E:\\cpp project\\Banking Services\\sounds\\welcome.wav"), NULL, SND_SYNC);
	if (a == 2)
		PlaySound(TEXT("E:\\cpp project\\Banking Services\\sounds\\collect.wav"), NULL, SND_SYNC);
	if (a == 3)
		PlaySound(TEXT("E:\\cpp project\\Banking Services\\sounds\\mix.wav"), NULL, SND_SYNC);
	if (a == 4)
		PlaySound(TEXT("E:\\cpp project\\Banking Services\\sounds\\thank_you.wav"), NULL, SND_SYNC);
}
void Gotoxy(int x, int y)
{

	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void Welcome()
{
	getch();
	int i, j, k, l;
	system("color 02");
	for (k = 185; k >= 15; k--)
	{

		Gotoxy(k, 5);
		cout << "-";
		Gotoxy(k, 45);
		cout << "-";
		Gotoxy(k, 10);
		cout << "-";
		Gotoxy(k, 40);
		cout << "-";
		Sleep(20);
	}
	for (l = 6; l < 46; l++)
	{

		Gotoxy(15, l);
		cout << "|\n";
		Gotoxy(185, l);
		cout << "|\n";
		Gotoxy(25, l);
		cout << "|\n";
		Gotoxy(175, l);
		cout << "|\n";
	}
	for (i = 50; i < 75; i++)
	{

		Gotoxy(i, 25);
		cout << " ";
		cout << "DIPTISH BANKING SERVICES";
		Sleep(20);
	}
	for (j = 120; j > 100; j--)
	{

		Gotoxy(j, 25);
		cout << "WELCOMES YOU";
		cout << "   ";
		Sleep(20);
	};
	Gotoxy(i, 26);
	cout << "____________________________";
	Gotoxy(j, 26);
	cout << "_____________";
	Gotoxy(164, 42);
	cout << "By Diptish ";
	Gotoxy(164, 43);
	cout << "__________ ";
	Gotoxy(0, 48);
	system("color F4");

	Play(1);
	system("color 02");

	system("pause");
	system("cls");
}
int main()
{
	 Welcome();

	Bank b;
	b.main_menu();
}
