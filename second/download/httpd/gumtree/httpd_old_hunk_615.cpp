    apr_status_t check;

    check = apr_stat(&sbuf, fname, APR_FINFO_TYPE, pool);
    return ((check || sbuf.filetype != APR_REG) ? 0 : 1);
}

/*
 * Copy from the current position of one file to the current position
 * of another.
 */
static void copy_file(FILE *target, FILE *source)
{
    static char line[MAX_STRING_LEN];

    while (fgets(line, sizeof(line), source) != NULL) {
	fputs(line, target);
    }
}

#ifdef NETWARE
void nwTerminate()
{
    pressanykey();
}
#endif

/*
 * Let's do it.  We end up doing a lot of file opening and closing,
 * but what do we care?  This application isn't run constantly.
 */
int main(int argc, const char * const argv[])
{
    FILE *ftemp = NULL;
    FILE *fpw = NULL;
    char user[MAX_STRING_LEN];
    char password[MAX_STRING_LEN];
    char record[MAX_STRING_LEN];
    char line[MAX_STRING_LEN];
    char pwfilename[MAX_STRING_LEN];
    const char *arg;
    int found = 0;
    int alg = ALG_CRYPT;
    int newfile = 0;
    int nofile = 0;
    int noninteractive = 0;
    int i;
    int args_left = 2;
    apr_pool_t *pool;
#if APR_CHARSET_EBCDIC
    apr_status_t rv;
    apr_xlate_t *to_ascii;
#endif

    apr_app_initialize(&argc, &argv, NULL);
    atexit(apr_terminate);
#ifdef NETWARE
    atexit(nwTerminate);
#endif
    apr_pool_create(&pool, NULL);

#if APR_CHARSET_EBCDIC
    rv = apr_xlate_open(&to_ascii, "ISO8859-1", APR_DEFAULT_CHARSET, pool);
    if (rv) {
        fprintf(stderr, "apr_xlate_open(to ASCII)->%d\n", rv);
        exit(1);
    }
    rv = apr_SHA1InitEBCDIC(to_ascii);
    if (rv) {
        fprintf(stderr, "apr_SHA1InitEBCDIC()->%d\n", rv);
        exit(1);
    }
    rv = apr_MD5InitEBCDIC(to_ascii);
    if (rv) {
        fprintf(stderr, "apr_MD5InitEBCDIC()->%d\n", rv);
        exit(1);
    }
#endif /*APR_CHARSET_EBCDIC*/

    tempfilename = NULL;
    apr_signal(SIGINT, (void (*)(int)) interrupted);

    /*
     * Preliminary check to make sure they provided at least
     * three arguments, we'll do better argument checking as 
     * we parse the command line.
     */
    if (argc < 3) {
        return usage();
    }

    /*
     * Go through the argument list and pick out any options.  They
     * have to precede any other arguments.
     */
