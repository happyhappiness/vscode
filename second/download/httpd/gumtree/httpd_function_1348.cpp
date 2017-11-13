static void usage(const char *error)
{
    if (error) {
    	apr_file_printf(errfile, "%s error: %s\n", shortname, error);
    }
	apr_file_printf(errfile,
    "%s -- program for cleaning the disk cache."                             NL
    "Usage: %s [-Dvtrn] -pPATH -lLIMIT"                                      NL
    "       %s [-nti] -dINTERVAL -pPATH -lLIMIT"                             NL
                                                                             NL
    "Options:"                                                               NL
    "  -d   Daemonize and repeat cache cleaning every INTERVAL minutes."     NL
    "       This option is mutually exclusive with the -D, -v and -r"        NL
    "       options."                                                        NL
                                                                             NL
    "  -D   Do a dry run and don't delete anything. This option is mutually" NL
    "       exclusive with the -d option."                                   NL
                                                                             NL
    "  -v   Be verbose and print statistics. This option is mutually"        NL
    "       exclusive with the -d option."                                   NL
                                                                             NL
    "  -r   Clean thoroughly. This assumes that the Apache web server is "   NL
    "       not running. This option is mutually exclusive with the -d"      NL
    "       option and implies -t."                                          NL
                                                                             NL
    "  -n   Be nice. This causes slower processing in favour of other"       NL
    "       processes."                                                      NL
                                                                             NL
    "  -t   Delete all empty directories. By default only cache files are"   NL
    "       removed, however with some configurations the large number of"   NL
    "       directories created may require attention."                      NL
                                                                             NL
    "  -p   Specify PATH as the root directory of the disk cache."           NL
                                                                             NL
    "  -l   Specify LIMIT as the total disk cache size limit. Attach 'K'"    NL
    "       or 'M' to the number for specifying KBytes or MBytes."           NL
                                                                             NL
    "  -i   Be intelligent and run only when there was a modification of"    NL
    "       the disk cache. This option is only possible together with the"  NL
    "       -d option."                                                      NL,
    shortname,
    shortname,
    shortname
    );

    exit(1);
}