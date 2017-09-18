    strcpy(record, user);
    strcat(record, ":");
    strcat(record, cpw);
    return 0;
}

static void usage(void)
{
    apr_file_printf(errfile, "Usage:\n");
    apr_file_printf(errfile, "\thtpasswd [-cmdps] passwordfile username\n");
    apr_file_printf(errfile, "\thtpasswd -b[cmdps] passwordfile username password\n\n");
    apr_file_printf(errfile, "\thtpasswd -n[mdps] username\n");
    apr_file_printf(errfile, "\thtpasswd -nb[mdps] username password\n");
    apr_file_printf(errfile, " -c  Create a new file.\n");
    apr_file_printf(errfile, " -n  Don't update file; display results on stdout.\n");
    apr_file_printf(errfile, " -m  Force MD5 encryption of the password"
#if defined(WIN32) || defined(TPF) || defined(NETWARE)
	" (default)"
#endif
	".\n");
    apr_file_printf(errfile, " -d  Force CRYPT encryption of the password"
#if (!(defined(WIN32) || defined(TPF) || defined(NETWARE)))
	    " (default)"
#endif
	    ".\n");
    apr_file_printf(errfile, " -p  Do not encrypt the password (plaintext).\n");
    apr_file_printf(errfile, " -s  Force SHA encryption of the password.\n");
    apr_file_printf(errfile, " -b  Use the password from the command line rather "
	    "than prompting for it.\n");
    apr_file_printf(errfile,
	    "On Windows, NetWare and TPF systems the '-m' flag is used by default.\n");
    apr_file_printf(errfile,
	    "On all other systems, the '-p' flag will probably not work.\n");
    exit(ERR_SYNTAX);
}

/*
 * Check to see if the specified file can be opened for the given
 * access.
 */
static int accessible(apr_pool_t *pool, char *fname, int mode)
{
    apr_file_t *f = NULL;

    if (apr_file_open(&f, fname, mode, APR_OS_DEFAULT, pool) != APR_SUCCESS) {
	return 0;
    }
    apr_file_close(f);
    return 1;
}

/*
 * Return true if a file is readable.
 */
static int readable(apr_pool_t *pool, char *fname)
{
    return accessible(pool, fname, APR_READ);
}

/*
 * Return true if the specified file can be opened for write access.
 */
static int writable(apr_pool_t *pool, char *fname)
{
    return accessible(pool, fname, APR_APPEND);
}

/*
 * Return true if the named file exists, regardless of permissions.
 */
static int exists(char *fname, apr_pool_t *pool)
