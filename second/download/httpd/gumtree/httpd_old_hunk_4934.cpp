    }
    /*
     * Make sure we still have exactly the right number of arguments left
     * (the filename, the username, and possibly the password if -b was
     * specified).
     */
    if ((argc - i) != args_left) {
        usage();
    }

    if (*mask & APHTP_NOFILE) {
        i--;
    }
    else {
        if (strlen(argv[i]) > (APR_PATH_MAX - 1)) {
            apr_file_printf(errfile, "%s: filename too long" NL, argv[0]);
            exit(ERR_OVERFLOW);
        }
        *pwfilename = apr_pstrdup(pool, argv[i]);
        if (strlen(argv[i + 1]) > (MAX_STRING_LEN - 1)) {
            apr_file_printf(errfile, "%s: username too long (> %d)" NL,
                argv[0], MAX_STRING_LEN - 1);
            exit(ERR_OVERFLOW);
        }
    }
    *user = apr_pstrdup(pool, argv[i + 1]);
    if ((arg = strchr(*user, ':')) != NULL) {
        apr_file_printf(errfile, "%s: username contains illegal "
                        "character '%c'" NL, argv[0], *arg);
        exit(ERR_BADUSER);
    }
    if (*mask & APHTP_NONINTERACTIVE) {
        if (strlen(argv[i + 2]) > (MAX_STRING_LEN - 1)) {
            apr_file_printf(errfile, "%s: password too long (> %d)" NL,
                argv[0], MAX_STRING_LEN);
            exit(ERR_OVERFLOW);
        }
        *password = apr_pstrdup(pool, argv[i + 2]);
    }
}

/*
 * Let's do it.  We end up doing a lot of file opening and closing,
 * but what do we care?  This application isn't run constantly.
 */
int main(int argc, const char * const argv[])
{
    apr_file_t *fpw = NULL;
    char record[MAX_STRING_LEN];
    char line[MAX_STRING_LEN];
    char *password = NULL;
    char *pwfilename = NULL;
    char *user = NULL;
    char tn[] = "htpasswd.tmp.XXXXXX";
    char *dirname;
    char *scratch, cp[MAX_STRING_LEN];
    int found = 0;
    int i;
    int alg = ALG_APMD5;
    int mask = 0;
    apr_pool_t *pool;
    int existing_file = 0;
#if APR_CHARSET_EBCDIC
    apr_status_t rv;
    apr_xlate_t *to_ascii;
#endif

    apr_app_initialize(&argc, &argv, NULL);
    atexit(terminate);
    apr_pool_create(&pool, NULL);
    apr_file_open_stderr(&errfile, pool);

#if APR_CHARSET_EBCDIC
    rv = apr_xlate_open(&to_ascii, "ISO-8859-1", APR_DEFAULT_CHARSET, pool);
    if (rv) {
        apr_file_printf(errfile, "apr_xlate_open(to ASCII)->%d" NL, rv);
        exit(1);
