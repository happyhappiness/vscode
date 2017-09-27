    struct logfile current; /* current logfile. */
    apr_pool_t *pool; /* top-level pool */
    char errbuf[ERRMSGSZ];
    int rotateReason;
    int tLogEnd;
    int nMessCount;
    int fileNum;
};

static rotate_config_t config;
static rotate_status_t status;

static void usage(const char *argv0, const char *reason)
{
    if (reason) {
        fprintf(stderr, "%s\n", reason);
    }
    fprintf(stderr,
#if APR_FILES_AS_SOCKETS
            "Usage: %s [-v] [-l] [-L linkname] [-p prog] [-f] [-t] [-e] [-c] [-n number] <logfile> "
#else
            "Usage: %s [-v] [-l] [-L linkname] [-p prog] [-f] [-t] [-e] [-n number] <logfile> "
#endif
            "{<rotation time in seconds>|<rotation size>(B|K|M|G)} "
            "[offset minutes from UTC]\n\n",
            argv0);
#ifdef OS2
    fprintf(stderr,
