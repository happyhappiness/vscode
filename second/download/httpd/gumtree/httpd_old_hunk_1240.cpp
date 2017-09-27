    );

    exit(1);
}
#undef NL

/*
 * main
 */
int main(int argc, const char * const argv[])
{
    apr_off_t max;
    apr_time_t current, repeat, delay, previous;
    apr_status_t status;
    apr_pool_t *pool, *instance;
    apr_getopt_t *o;
    apr_finfo_t info;
    int retries, isdaemon, limit_found, intelligent, dowork;
    char opt;
    const char *arg;
    char *proxypath, *path;
    char errmsg[1024];

    interrupted = 0;
    repeat = 0;
    isdaemon = 0;
    dryrun = 0;
