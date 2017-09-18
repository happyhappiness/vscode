    strcpy(record, user);
    strcat(record, ":");
    strcat(record, cpw);
    return 0;
}

static int usage(void)
{
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "\thtpasswd [-cmdps] passwordfile username\n");
    fprintf(stderr, "\thtpasswd -b[cmdps] passwordfile username password\n\n");
    fprintf(stderr, "\thtpasswd -n[mdps] username\n");
    fprintf(stderr, "\thtpasswd -nb[mdps] username password\n");
    fprintf(stderr, " -c  Create a new file.\n");
    fprintf(stderr, " -n  Don't update file; display results on stdout.\n");
    fprintf(stderr, " -m  Force MD5 encryption of the password"
#if defined(WIN32) || defined(TPF) || defined(NETWARE)
	" (default)"
#endif
	".\n");
    fprintf(stderr, " -d  Force CRYPT encryption of the password"
#if (!(defined(WIN32) || defined(TPF) || defined(NETWARE)))
	    " (default)"
#endif
	    ".\n");
    fprintf(stderr, " -p  Do not encrypt the password (plaintext).\n");
    fprintf(stderr, " -s  Force SHA encryption of the password.\n");
    fprintf(stderr, " -b  Use the password from the command line rather "
	    "than prompting for it.\n");
    fprintf(stderr,
	    "On Windows, NetWare and TPF systems the '-m' flag is used by default.\n");
    fprintf(stderr,
	    "On all other systems, the '-p' flag will probably not work.\n");
    return ERR_SYNTAX;
}

static void interrupted(void)
{
    fprintf(stderr, "Interrupted.\n");
    if (tempfilename != NULL) {
	unlink(tempfilename);
    }
    exit(ERR_INTERRUPTED);
}

/*
 * Check to see if the specified file can be opened for the given
 * access.
 */
static int accessible(char *fname, char *mode)
{
    FILE *s;

    s = fopen(fname, mode);
    if (s == NULL) {
	return 0;
    }
    fclose(s);
    return 1;
}

/*
 * Return true if a file is readable.
 */
static int readable(char *fname)
{
    return accessible(fname, "r");
}

/*
 * Return true if the specified file can be opened for write access.
 */
static int writable(char *fname)
{
    return accessible(fname, "a");
}

/*
 * Return true if the named file exists, regardless of permissions.
 */
static int exists(char *fname, apr_pool_t *pool)
