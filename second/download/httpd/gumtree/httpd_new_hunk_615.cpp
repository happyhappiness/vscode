    apr_status_t check;

    check = apr_stat(&sbuf, fname, APR_FINFO_TYPE, pool);
    return ((check || sbuf.filetype != APR_REG) ? 0 : 1);
}

#ifdef NETWARE
void nwTerminate()
{
    pressanykey();
}
#endif

static void check_args(apr_pool_t *pool, int argc, const char *const argv[], 
                       int *alg, int *mask, char **user, char **pwfilename, 
                       char **password)
{
    const char *arg;
    int args_left = 2;
    int i;

    /*
     * Preliminary check to make sure they provided at least
     * three arguments, we'll do better argument checking as 
     * we parse the command line.
     */
    if (argc < 3) {
        usage();
    }

    /*
     * Go through the argument list and pick out any options.  They
     * have to precede any other arguments.
     */
