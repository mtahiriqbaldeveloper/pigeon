/* pigeon.h */
#pragma once
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <birchutils.h>

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;

enum e_state {
    idle = 0,
    connecting = 1,
    connected = 2,
    hello = 3,
    mail = 4,
    recepient = 5,
    data = 6,
    payload = 7,
    disconnecting = 8
};

typedef enum e_state State;

struct s_email {
    State state;
    int8 src[128];
    int8 dest[128];
    int8 id[128];
    int8 subject[128];
    int8 *domain;
    int8 data[];
};

typedef struct s_email Email;

struct s_server {
    int8 domain[128];
    int8 server[128];
    int32 ip;
};

typedef struct s_server Server;


#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $c (char *)
#define $i (int)

bool sendmail(Email *, const Server *);

#define log(f, args ...)    printf(f, args)

int main(int, char **);
