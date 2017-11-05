static apr_status_t hm_file_update_stat(hm_ctx_t *ctx, hm_server_t *s, apr_pool_t *pool)
{
    apr_status_t rv;
    apr_file_t *fp;
    apr_file_t *fpin;
    apr_time_t now;
    apr_time_t fage;
    apr_finfo_t fi;
    int updated = 0;
    char *path = apr_pstrcat(pool, ctx->storage_path, ".tmp.XXXXXX", NULL);


    /* TODO: Update stats file (!) */
    rv = apr_file_mktemp(&fp, path, APR_CREATE | APR_WRITE, pool);

    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                     "Heartmonitor: Unable to open tmp file: %s", path);
        return rv;
    }
    rv = apr_file_open(&fpin, ctx->storage_path, APR_READ|APR_BINARY|APR_BUFFERED,
                       APR_OS_DEFAULT, pool);

    now = apr_time_now();
    if (rv == APR_SUCCESS) {
        char *t;
        apr_table_t *hbt = apr_table_make(pool, 10);
        apr_bucket_alloc_t *ba = apr_bucket_alloc_create(pool);
        apr_bucket_brigade *bb = apr_brigade_create(pool, ba);
        apr_bucket_brigade *tmpbb = apr_brigade_create(pool, ba);
        rv = apr_file_info_get(&fi, APR_FINFO_SIZE | APR_FINFO_MTIME, fpin);
        if (rv) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                         "Heartmonitor: Unable to read file: %s", ctx->storage_path);
            return rv;
        }

        /* Read the file and update the line corresponding to the node */
        ba = apr_bucket_alloc_create(pool);
        bb = apr_brigade_create(pool, ba);
        apr_brigade_insert_file(bb, fpin, 0, fi.size, pool);
        tmpbb = apr_brigade_create(pool, ba);
        fage = apr_time_sec(now - fi.mtime);
        do {
            char buf[4096];
            const char *ip;
            apr_size_t bsize = sizeof(buf);
            apr_brigade_cleanup(tmpbb);
            if (APR_BRIGADE_EMPTY(bb)) {
                break;
            } 
            rv = apr_brigade_split_line(tmpbb, bb,
                                        APR_BLOCK_READ, sizeof(buf));
       
            if (rv) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                             "Heartmonitor: Unable to read from file: %s", ctx->storage_path);
                return rv;
            }

            apr_brigade_flatten(tmpbb, buf, &bsize);
            if (bsize == 0) {
                break;
            }
            buf[bsize - 1] = 0;
            t = strchr(buf, ' ');
            if (t) {
                ip = apr_pstrndup(pool, buf, t - buf);
            } else {
                ip = NULL;
            }
            if (!ip || buf[0] == '#') {
                /* copy things we can't process */
                apr_file_printf(fp, "%s\n", buf);
            } else if (strcmp(ip, s->ip) !=0 ) {
                hm_server_t node; 
                apr_time_t seen;
                /* Update seen time according to the last file modification */
                apr_table_clear(hbt);
                qs_to_table(apr_pstrdup(pool, t), hbt, pool);
                if (apr_table_get(hbt, "busy")) {
                    node.busy = atoi(apr_table_get(hbt, "busy"));
                } else {
                    node.busy = 0;
                }

                if (apr_table_get(hbt, "ready")) {
                    node.ready = atoi(apr_table_get(hbt, "ready"));
                } else {
                    node.ready = 0;
                }

                if (apr_table_get(hbt, "lastseen")) {
                    node.seen = atoi(apr_table_get(hbt, "lastseen"));
                } else {
                    node.seen = SEEN_TIMEOUT; 
                }
                seen = fage + node.seen;

                if (apr_table_get(hbt, "port")) {
                    node.port = atoi(apr_table_get(hbt, "port"));
                } else {
                    node.port = 80; 
                }
                apr_file_printf(fp, "%s &ready=%u&busy=%u&lastseen=%u&port=%u\n",
                                ip, node.ready, node.busy, (unsigned int) seen, node.port);
            } else {
                apr_time_t seen;
                seen = apr_time_sec(now - s->seen);
                apr_file_printf(fp, "%s &ready=%u&busy=%u&lastseen=%u&port=%u\n",
                                s->ip, s->ready, s->busy, (unsigned int) seen, s->port);
                updated = 1;
            }
        } while (1);
    }

    if (!updated) {
        apr_time_t seen;
        seen = apr_time_sec(now - s->seen);
        apr_file_printf(fp, "%s &ready=%u&busy=%u&lastseen=%u&port=%u\n",
                        s->ip, s->ready, s->busy, (unsigned int) seen, s->port);
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

    rv = apr_file_rename(path, ctx->storage_path, pool);

    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                     "Heartmonitor: Unable to move file: %s -> %s", path,
                     ctx->storage_path);
        return rv;
    }

    return APR_SUCCESS;
}