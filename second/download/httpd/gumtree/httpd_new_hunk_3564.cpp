    return (int)apr_time_sec(tNow) + utc_offset;
}

/*
 * Close a file and destroy the associated pool.
 */
static void close_logfile(rotate_config_t *config, struct logfile *logfile)
{
    if (config->verbose) {
        fprintf(stderr, "Closing file %s\n", logfile->name);
    }
    apr_file_close(logfile->fd);
    apr_pool_destroy(logfile->pool);
}

/*
 * Dump the configuration parsing result to STDERR.
 */
static void dumpConfig (rotate_config_t *config)
