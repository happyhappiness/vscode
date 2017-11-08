static void close_logfile(rotate_config_t *config, struct logfile *logfile)
{
    if (config->verbose) {
        fprintf(stderr, "Closing file %s\n", logfile->name);
    }
    apr_file_close(logfile->fd);
    apr_pool_destroy(logfile->pool);
}