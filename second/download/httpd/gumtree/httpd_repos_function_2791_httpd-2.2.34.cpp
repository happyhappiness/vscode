static RETCODE freetds_exec(DBPROCESS *proc, const char *query,
                            int want_results, int *nrows)
{
    /* TBD */
    RETCODE rv = dbcmd(proc, query);
    if (rv != SUCCEED) {
        return rv;
    }
    rv = dbsqlexec(proc);
    if (rv != SUCCEED) {
        return rv;
    }
    if (!want_results) {
        while (dbresults(proc) != NO_MORE_RESULTS) {
            ++*nrows;
        }
    }
    return SUCCEED;
}