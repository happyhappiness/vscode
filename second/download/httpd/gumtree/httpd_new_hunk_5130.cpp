                config->postrotate_prog,
                apr_strerror(rv, error, sizeof(error)));
        return;
    }
}

/* After a error, truncate the current file and write out an error
 * message, which must be contained in status->errbuf.  The process is
 * terminated on failure.  */
static void truncate_and_write_error(rotate_status_t *status)
{
    apr_size_t buflen = strlen(status->errbuf);

    if (apr_file_trunc(status->current.fd, 0) != APR_SUCCESS) {
        fprintf(stderr, "Error truncating the file %s\n", status->current.name);
        exit(2);
    }
    if (apr_file_write_full(status->current.fd, status->errbuf, buflen, NULL) != APR_SUCCESS) {
        fprintf(stderr, "Error writing error (%s) to the file %s\n", 
                status->errbuf, status->current.name);
        exit(2);
    }
}

/*
 * Open a new log file, and if successful
 * also close the old one.
 *
 * The timestamp for the calculation of the file
 * name of the new log file will be the actual millisecond
