        /* Try to keep this error message constant length
         * in case it occurs several times. */
        apr_snprintf(status->errbuf, sizeof status->errbuf,
                     "Resetting log file due to error opening "
                     "new log file, %10d messages lost: %-25.25s\n",
                     status->nMessCount, error);
        nWrite = strlen(status->errbuf);

        if (apr_file_trunc(status->current.fd, 0) != APR_SUCCESS) {
            fprintf(stderr, "Error truncating the file %s\n", status->current.name);
            exit(2);
        }
        if (apr_file_write_full(status->current.fd, status->errbuf, nWrite, NULL) != APR_SUCCESS) {
            fprintf(stderr, "Error writing to the file %s\n", status->current.name);
            exit(2);
        }
    }

    status->nMessCount = 0;
}

/*
