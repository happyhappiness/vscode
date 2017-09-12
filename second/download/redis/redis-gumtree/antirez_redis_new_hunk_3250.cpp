
#define SDS_ABORT_ON_OOM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sds.h"

static void sdsOomAbort(void) {
    fprintf(stderr,"SDS: Out Of Memory (SDS_ABORT_ON_OOM defined)\n");
