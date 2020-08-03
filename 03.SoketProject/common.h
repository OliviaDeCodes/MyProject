/*************************************************************************
	> File Name: common.h
	> Author: Lifaqiang
	> Mail: 576245069@qq.com 
	> Created Time: 日 11/18 09:14:06 2018
 ************************************************************************/

#ifndef _HEAD_H
#include <pthread.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>

#define max_size 1024
#define _HEAD_H
#endif

#ifdef DBG
#define DBG(fmt,args...) printf(fmt,##args)
#else
#define DBG(fmt,args...)
#endif
