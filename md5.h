#pragma once
#ifndef _MD5H_
#define _MD5H_
#include <math.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

void ROL(unsigned int& s, unsigned short cx);
void ltob(unsigned int& i); 
unsigned int* MD5(const char* mStr); 
unsigned int* MD5_2(const char* mStr);
#endif

