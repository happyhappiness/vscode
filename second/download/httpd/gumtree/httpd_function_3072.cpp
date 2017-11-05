static apr_status_t hm_file_update_stats(hm_ctx_t *ctx, apr_pool_t *p)
{
    apr_status_t rv;
    apr_file_t *fp;
    apr_hash_index_t *hi;
    apr_time_t now;
    char *path = apr_pstrcat(p, ctx->storage_path, ".tmp.XXXXXX", NULL);
    /* TODO: Update stats file (!) */
    rv = apr_file_mktemp(&fp, path, APR_CREATE | APR_WRITE, p);

    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                     "Heartmonitor: Unable to open tmp file: %s", path);
        return rv;
    }

    now = apr_time_now();
    for (hi = apr_hash_first(p, ctx->servers);
         hi != NULL; hi = apr_hash_next(hi)) {
        hm_server_t *s = NULL;
        apr_time_t seen;
        apr_hash_this(hi, NULL, NULL, (void **) &s);
        seen = apr_time_sec(now - s->seen);
        if (seen > SEEN_TIMEOUT) {
            /*
             * Skip this entry from the heartbeat file -- when it comes back,
             * we will reuse the memory...
             */
        }
        else {
            apr_file_printf(fp, "%s &ready=%u&busy=%u&lastseen=%u&port=%u\n",
                            s->ip, s->ready, s->busy, (unsigned int) seen, s->port);
        }
    }

    rv = apr_file_flush(fp);
    if (rv) {
      ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                   "Heartmonitor: Unable to flush file: %s", path);
      return rv;
    }

    rv = apr_file_close(fp);
    if (rv) {
      ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                   "Heartmonitor: Unable to close file: %s", path);
      return rv;
    }
  
    rv = apr_file_perms_set(path,
                            APR_FPROT_UREAD | APR_FPROT_GREAD |
                            APR_FPROT_WREAD);
    if (rv && rv != APR_INCOMPLETE) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                     "Heartmonitor: Unable to set file permssions on %s",
                     path);
        return rv;
    }

    rv = apr_file_rename(path, ctx->storage_path, p);

    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                     "Heartmonitor: Unable to move file: %s -> %s", path,
                     ctx->storage_path);
        return rv;
    }

    return APR_SUCCESS;
}