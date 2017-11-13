apr_file_printf(errfile,
                        "Could not remove file '%s': %s" APR_EOL_STR, file,
                        apr_strerror(rv, errmsg, sizeof errmsg));