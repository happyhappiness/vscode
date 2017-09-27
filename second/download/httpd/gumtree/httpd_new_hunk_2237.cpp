#endif
#if APR_HAVE_STRINGS_H
#include <strings.h>
#endif

#define BUFSIZE         65536
#define ERRMSGSZ        256

#ifndef MAX_PATH
#define MAX_PATH        1024
#endif

static void usage(const char *argv0, const char *reason)
{
    if (reason) {
        fprintf(stderr, "%s\n", reason);
    }
    fprintf(stderr,
            "Usage: %s [-l] [-f] <logfile> "
            "{<rotation time in seconds>|<rotation size in megabytes>} "
            "[offset minutes from UTC]\n\n",
            argv0);
#ifdef OS2
    fprintf(stderr,
            "Add this:\n\nTransferLog \"|%s.exe /some/where 86400\"\n\n",
