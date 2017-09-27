                config->postrotate_prog,
                apr_strerror(rv, error, sizeof(error)));
        return;
    }
}

/*
 * Open a new log file, and if successful
 * also close the old one.
 *
 * The timestamp for the calculation of the file
 * name of the new log file will be the actual millisecond
