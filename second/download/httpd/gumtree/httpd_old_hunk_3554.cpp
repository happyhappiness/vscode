{
    if (error) {
        apr_file_printf(errfile, "%s error: %s\n", shortname, error);
    }
    apr_file_printf(errfile,
    "%s -- program for cleaning the disk cache."                             NL
    "Usage: %s [-Dvtrn] -pPATH -lLIMIT [-PPIDFILE]"                          NL
    "       %s [-nti] -dINTERVAL -pPATH -lLIMIT [-PPIDFILE]"                 NL
    "       %s [-Dvt] -pPATH URL ..."                                        NL
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
