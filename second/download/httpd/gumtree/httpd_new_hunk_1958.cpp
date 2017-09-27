#include "apr_time.h"
#include "apr_getopt.h"

#if APR_HAVE_STDLIB_H
#include <stdlib.h>
#endif
#define APR_WANT_STRFUNC
#include "apr_want.h"

#define BUFSIZE         65536
#define ERRMSGSZ        256

#ifndef MAX_PATH
#define MAX_PATH        1024
#endif

#define ROTATE_NONE     0
#define ROTATE_NEW      1
#define ROTATE_TIME     2
#define ROTATE_SIZE     3
#define ROTATE_FORCE    4

static const char *ROTATE_REASONS[] = {
    "None",
    "Open a new file",
    "Time interval expired",
    "Maximum size reached",
    "Forced rotation",
    NULL
};

typedef struct rotate_config rotate_config_t;

struct rotate_config {
    unsigned int sRotation;
    int tRotation;
    int utc_offset;
    int use_localtime;
    int use_strftime;
    int force_open;
    int verbose;
    const char *szLogRoot;
    int truncate;
    const char *linkfile;
};

typedef struct rotate_status rotate_status_t;

struct rotate_status {
    apr_pool_t *pool;
    apr_pool_t *pfile;
    apr_pool_t *pfile_prev;
    apr_file_t *nLogFD;
    apr_file_t *nLogFDprev;
    char filename[MAX_PATH];
    char errbuf[ERRMSGSZ];
    int rotateReason;
    int tLogEnd;
    int nMessCount;
};

static rotate_config_t config;
static rotate_status_t status;

static void usage(const char *argv0, const char *reason)
{
    if (reason) {
        fprintf(stderr, "%s\n", reason);
    }
    fprintf(stderr,
            "Usage: %s [-v] [-l] [-L linkname] [-f] [-t] <logfile> "
            "{<rotation time in seconds>|<rotation size>(B|K|M|G)} "
            "[offset minutes from UTC]\n\n",
            argv0);
#ifdef OS2
    fprintf(stderr,
            "Add this:\n\nTransferLog \"|%s.exe /some/where 86400\"\n\n",
            argv0);
