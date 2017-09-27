        /* Try to keep this error message constant length
         * in case it occurs several times. */
        apr_snprintf(status->errbuf, sizeof status->errbuf,
                     "Resetting log file due to error opening "
                     "new log file, %10d messages lost: %-25.25s\n",
                     status->nMessCount, error);

        truncate_and_write_error(status);
    }

    status->nMessCount = 0;
}

/*
