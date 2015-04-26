//Autor: Siegfried Paul Keller Schippner
//date: release: 20.12.2014
//This code is property of Siegfried Keller.

#include <iostream>
#include <cstring>
#include <string> //find, size_t
//#include <unistd.h> //excel for linux
//int ch = cin.get();
#include <sys/time.h> /* struct timeval, select() */
/* ICANON, ECHO, TCSANOW, struct termios */
#include <termios.h> /* tcgetattr(), tcsetattr() */
#include <stdlib.h> /* atexit(), exit() */
#include <unistd.h> /* read() */
#include <stdio.h> /* printf() */

using namespace std;

static struct termios g_old_kbd_mode;
/*****************************************************************************
*****************************************************************************/
static void cooked(void)
{
	tcsetattr(0, TCSANOW, &g_old_kbd_mode);
}
/*****************************************************************************
*****************************************************************************/
static void raw(void)
{
	static char init;
/**/
	struct termios new_kbd_mode;

	if(init)
		return;
/* put keyboard (stdin, actually) in raw, unbuffered mode */
	tcgetattr(0, &g_old_kbd_mode);
	memcpy(&new_kbd_mode, &g_old_kbd_mode, sizeof(struct termios));
	new_kbd_mode.c_lflag &= ~(ICANON | ECHO);
	new_kbd_mode.c_cc[VTIME] = 0;
	new_kbd_mode.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_kbd_mode);
/* when we exit, go back to normal, "cooked" mode */
	atexit(cooked);

	init = 1;
}
/*****************************************************************************
*****************************************************************************/
static int kbhit(void)
{
	struct timeval timeout;
	fd_set read_handles;
	int status;

	raw();
/* check stdin (fd 0) for activity */
	FD_ZERO(&read_handles);
	FD_SET(0, &read_handles);
	timeout.tv_sec = timeout.tv_usec = 0;
	status = select(0 + 1, &read_handles, NULL, NULL, &timeout);
	if(status < 0)
	{
		printf("select() failed in kbhit()\n");
		exit(1);
	}
	return status;
}
/*****************************************************************************
*****************************************************************************/
static int getch(void)
{
	unsigned char temp;

	raw();
/* stdin = fd 0 */
	if(read(0, &temp, 1) != 1)
		return 0;
	return temp;
}
//-----------------------------------------------------------

//using namespace std;

void Keys();
void exec();
void itext();
void menu();
void shell();

int Key;
string input;
string exe = "/usr/bin/adb";

int main(){
	menu();
	while(1/*!kbhit()*/){
		Key = getch();
		usleep(0.01);
	    Keys();
	}
}

void menu(){
	cout << "|-------------------------------------------|\n";
	cout << "|--#######################################--|\n";
	cout << "|--| PC Keyboard for Android 2.0         |--|\n";
	cout << "|--#######################################--|\n";
	cout << "|--|   Programmed by Siegfried Keller    |--|\n";
	cout << "|--#######################################--|\n";
	cout << "|--|-------------------------------------|--|\n";
	cout << "|--|                                     |--|\n";
	cout << "|--| read README.txt                     |--|\n";
	cout << "|--| to check working keys, info about   |--|\n";
	cout << "|--| the application.                    |--|\n";
	cout << "|--|                                     |--|\n";
	cout << "|--|-------------------------------------|--|\n";
	cout << "|--|                                     |--|\n";
	cout << "|--| mail: kellex_urps@hotmail.com       |--|\n";
	cout << "|--| websites: kellex.ucoz.com           |--|\n";
	cout << "|--|           zevenhead.blogspot.com    |--|\n";
	cout << "|--| (C) Siegfried Keller 2015           |--|\n";
	cout << "|--|                                     |--|\n";
	cout << "|--|-------------------------------------|--|\n";
	cout << "|-------------------------------------------|\n";
	cout << "\n\n";
}

void exec(){
	int fork_rv = fork();
	if(fork_rv == 0){
		execl(exe.c_str(),"adb","shell","input","keyevent",input.c_str(),(char *)NULL);
		_exit(1);
	}
	input = "";
}

void itext(){
	int fork_rv = fork();
	if(fork_rv == 0){
		execl(exe.c_str(),"adb","shell","input","text",input.c_str(),(char *)NULL);
		_exit(1);
	}
	input = "";
}

void Keys(){
	switch(Key){
		case 91://HOME [
		input = "3";
		exec();
		break;
		case 93://Back ]
		input = "4";
		exec();
		break;
		case 74://Up
		input = "21";
		exec();
		break;
		case 76://Down
		input = "20";
		exec();
		break;
		case 75://Left
		input = "21";
		exec();
		break;
		case 77://Right
		input = "22";
		exec();
		break;
		case 39://Center '
		input = "23";
		exec();
		break;
		case 63://?
		input = "?";
		itext();
		break;
		case 61://=
		input = "=";
		itext();
		break;
		case 42://star
		input = "17";
		exec();
		break;
		case 46://.
		input = "56";
		exec();
		break;
		case 44://,
		input = "55";
		exec();
		break;
		case 45://-
		input = "69";
		exec();
		break;
		case 48://0
		input = "7";
		exec();
		break;
		case 49://1
		input = "8";
		exec();
		break;
		case 50://2
		input = "9";
		exec();
		break;
		case 51://3
		input = "10";
		exec();
		break;
		case 52://4
		input = "11";
		exec();
		break;
		case 53://5
		input = "12";
		exec();
		break;
		case 54://6
		input = "13";
		exec();
		break;
		case 55://7
		input = "14";
		exec();
		break;
		case 56://8
		input = "15";
		exec();
		break;
		case 57://9
		input = "16";
		exec();
		break;
		case 127://Delete
		input = "67";
		exec();
		break;
		case 32://Space
		input = "62";
		exec();
		break;
		case 10://Enter
		input = "66";
		exec();
		break;
		case 97://a
		input = "29";
		exec();
		break;
		case 98://b
		input = "30";
		exec();
		break;
		case 99://c
		input = "31";
		exec();
		break;
		case 100://d
		input = "32";
		exec();
		break;
		case 101://e
		input = "33";
		exec();
		break;
		case 102://f
		input = "34";
		exec();
		break;
		case 103://g
		input = "35";
		exec();
		break;
		case 104://h
		input = "36";
		exec();
		break;
		case 105://i
		input = "37";
		exec();
		break;
		case 106://j
		input = "38";
		exec();
		break;
		case 107://k
		input = "39";
		exec();
		break;
		case 108://l
		input = "40";
		exec();
		break;
		case 109://m
		input = "41";
		exec();
		break;
		case 110://n
		input = "42";
		exec();
		break;
		case 111://o
		input = "43";
		exec();
		break;
		case 112://p
		input = "44";
		exec();
		break;
		case 113://q
		input = "45";
		exec();
		break;
		case 114://r
		input = "46";
		exec();
		break;
		case 115://s
		input = "47";
		exec();
		break;
		case 116://t
		input = "48";
		exec();
		break;
		case 117://u
		input = "49";
		exec();
		break;
		case 118://v
		input = "50";
		exec();
		break;
		case 119://w
		input = "51";
		exec();
		break;
		case 120://x
		input = "52";
		exec();
		break;
		case 121://y
		input = "53";
		exec();
		break;
		case 122://z
		input = "54";
		exec();
		break;/*
		case 101://e
		if(fork_rv == 0){
			execl(exe.c_str(),"adb","shell","input","keyevent","33",0);
			_exit(1);
		}
		break;*/
	}
}
