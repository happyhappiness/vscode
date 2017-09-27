
    /* process remaining entries oldest to newest, the check for an emtpy
     * ring actually isn't necessary except when the compiler does
     * corrupt 64bit arithmetics which happend to me once, so better safe
     * than sorry
     */
    while (sum > max && !interrupted && !APR_RING_EMPTY(&root, _entry, link)) {
        oldest = APR_RING_FIRST(&root);

        for (e = APR_RING_NEXT(oldest, link);
             e != APR_RING_SENTINEL(&root, _entry, link);
             e = APR_RING_NEXT(e, link)) {
            if (e->dtime < oldest->dtime) {
                oldest = e;
            }
        }

        delete_entry(path, oldest->basename, pool);
        sum -= oldest->hsize;
        sum -= oldest->dsize;
        entries--;
        APR_RING_REMOVE(oldest, link);
    }

    if (!interrupted) {
        printstats(total, sum, max, etotal, entries);
    }
}

/*
 * usage info
 */
#define NL APR_EOL_STR
static void usage(const char *error)
{
    if (error) {
    	apr_file_printf(errfile, "%s error: %s\n", shortname, error);
    }
	apr_file_printf(errfile,
    "%s -- program for cleaning the disk cache."                             NL
    "Usage: %s [-Dvtrn] -pPATH -lLIMIT [-PPIDFILE]"                          NL
    "       %s [-nti] -dINTERVAL -pPATH -lLIMIT [-PPIDFILE]"                 NL
                                                                             NL
    "Options:"                                                               NL
    "  -d   Daemonize and repeat cache cleaning every INTERVAL minutes."     NL
    "       This option is mutually exclusive with the -D, -v and -r"        NL
    "       options."                                                        NL
                                                                             NL
