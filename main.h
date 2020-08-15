#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <iostream>
#include<winsock.h>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib")

#ifdef _WIN32
#include <Windows.h>
#endif


typedef int Status;

#define OK              1
#define ERROR           0

#include "strategy.h"
#include "player.h"
#include "model.h"


static const int BUFSIZE = 1024;
static SOCKET m_server;
static const char* IP = "127.0.0.1";
static const int PORT = 7788;

extern float sweepDistance;

void DeleteNL(char* Message);