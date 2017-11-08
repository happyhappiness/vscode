static apr_status_t cerr(apr_getopt_t *os, const char *err, int ch,
                         apr_status_t status)
{
    if (os->errfn)
        (os->errfn)(os->errarg, "%s: %s: %c\n", 
                    apr_filepath_name_get(*os->argv), err, ch);
    return status;
}