                            const char *description)
{
    apr_file_t *stderr_log;
    char errbuf[200];

    apr_file_open_stderr(&stderr_log, pool);
    apr_file_printf(stderr_log,
                    "(%d)%s: %s\n",
                    err,
                    apr_strerror(err, errbuf, sizeof(errbuf)),
                    description);
}

static apr_status_t run_cgi_child(apr_file_t **script_out,
                                  apr_file_t **script_in,
                                  apr_file_t **script_err, 
                                  const char *command,
