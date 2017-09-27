            intelligent = 1;
            dowork = 1;
            break;
        }

        if (dowork && !interrupted) {
            if (!process_dir(path, instance) && !interrupted) {
                purge(path, instance, max);
            }
            else if (!isdaemon && !interrupted) {
                apr_file_printf(errfile, "An error occurred, cache cleaning "
                                         "aborted." APR_EOL_STR);
                return 1;
            }
