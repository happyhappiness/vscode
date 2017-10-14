apr_file_printf(errfile, "apr_xlate_open(): %s (%d)\n",
                apr_strerror(rv, line, sizeof(line)), rv);