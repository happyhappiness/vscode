apr_file_printf(errfile,
                            "Could not write the pid file '%s': %s" APR_EOL_STR,
                            pidfilename, 
                            apr_strerror(status, errmsg, sizeof errmsg));