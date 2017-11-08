static void usage(void)
{
    apr_file_printf(errfile,
    "%s -- Resolve IP-addresses to hostnames in Apache log files."           NL
    "Usage: %s [-s STATFILE] [-c]"                                           NL
                                                                             NL
    "Options:"                                                               NL
    "  -s   Record statistics to STATFILE when finished."                    NL
                                                                             NL
    "  -c   Perform double lookups when resolving IP addresses."             NL,
    shortname, shortname);
    exit(1);
}