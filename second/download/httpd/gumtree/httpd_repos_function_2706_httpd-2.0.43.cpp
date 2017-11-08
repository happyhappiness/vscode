static apr_status_t cerr(apr_getopt_t *os, const char *err, int ch,
                         apr_status_t status)
{
    if (os->errfn)
        (os->errfn)(os->errarg, "%s: %s: %c\n", 
                    apr_filename_of_pathname(*os->argv), err, ch);
    return status;
}