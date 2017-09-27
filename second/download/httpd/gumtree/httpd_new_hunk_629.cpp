    /* Sendfile not supported by this OS */
    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                 "mod_file_cache: unable to cache file: %s. Sendfile is not supported on this OS", filename);
#endif
    return NULL;
}
static const char *cachefilemmap(cmd_parms *cmd, void *dummy, const char *filename)
{
#if APR_HAS_MMAP
    cache_the_file(cmd, filename, 1);
#else
    /* MMAP not supported by this OS */
    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
