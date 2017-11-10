static int freetds_err_handler(DBPROCESS *dbproc, int severity, int dberr,
                               int oserr, char *dberrstr, char *oserrstr)
{
    return INT_CANCEL; /* never exit */
}