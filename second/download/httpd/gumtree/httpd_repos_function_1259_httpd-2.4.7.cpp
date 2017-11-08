static const char *cachefilemmap(cmd_parms *cmd, void *dummy, const char *filename)
{
#if APR_HAS_MMAP
    cache_the_file(cmd, filename, 1);
#else
    /* MMAP not supported by this OS */
    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00801)
                 "unable to cache file: %s. MMAP is not supported by this OS", filename);
#endif
    return NULL;
}