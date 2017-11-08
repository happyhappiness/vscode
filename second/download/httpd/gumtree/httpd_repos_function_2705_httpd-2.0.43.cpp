static apr_status_t serr(apr_getopt_t *os, const char *err, const char *str,
                         apr_status_t status)
{
    if (os->errfn)
        (os->errfn)(os->errarg, "%s: %s: %s\n", 
                    apr_filename_of_pathname(*os->argv), err, str);
    return status;
}