apr_file_printf(errfile, "Could not remove directory %s: %pm" APR_EOL_STR,
                    dir, &rv);