        apr_file_printf(*pidfile, "%" APR_PID_T_FMT APR_EOL_STR, mypid);
    }
    else {
        if (errfile) {
            apr_file_printf(errfile,
                            "Could not write the pid file '%s': %s" APR_EOL_STR,
                            pidfilename, 
                            apr_strerror(status, errmsg, sizeof errmsg));
        }
        exit(1);
    }
}

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
    apr_file_t *pidfile;
    int retries, isdaemon, limit_found, intelligent, dowork;
    char opt;
    const char *arg;
    char *proxypath, *path, *pidfilename;
    char errmsg[1024];

    interrupted = 0;
    repeat = 0;
    isdaemon = 0;
    dryrun = 0;
    limit_found = 0;
    max = 0;
    verbose = 0;
    realclean = 0;
    benice = 0;
    deldirs = 0;
    intelligent = 0;
    previous = 0; /* avoid compiler warning */
