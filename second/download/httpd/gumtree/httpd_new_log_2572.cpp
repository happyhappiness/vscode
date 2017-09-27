apr_file_printf(errfile, "Could not remove directory %s: %s" APR_EOL_STR,
                    dir, apr_strerror(rv, errmsg, sizeof errmsg));