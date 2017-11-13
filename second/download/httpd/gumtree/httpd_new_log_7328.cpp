apr_file_printf(errfile, "Could not open passwd file %s for writing: %pm\n",
                    argv[2], &rv);