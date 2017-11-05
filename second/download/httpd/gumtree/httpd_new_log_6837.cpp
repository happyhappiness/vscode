apr_file_printf(errfile,
                            "Could not write the pid file '%s': %pm" APR_EOL_STR,
                            pidfilename, &status);