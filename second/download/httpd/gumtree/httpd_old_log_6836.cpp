apr_file_printf(errfile, "Could not remove file %s: %s" APR_EOL_STR,
                        remove, apr_strerror(status, errmsg, sizeof errmsg));