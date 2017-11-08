static apr_status_t readfile_heartbeats(const char *path, apr_hash_t *servers,
                                    apr_pool_t *pool)
{
    apr_finfo_t fi;
    apr_status_t rv;
    apr_file_t *fp;

    if (!path) {
        return APR_SUCCESS;
    }

    rv = apr_file_open(&fp, path, APR_READ|APR_BINARY|APR_BUFFERED,
                       APR_OS_DEFAULT, pool);

    if (rv) {
        return rv;
    }

    rv = apr_file_info_get(&fi, APR_FINFO_SIZE, fp);

    if (rv) {
        return rv;
    }

    {
        char *t;
        int lineno = 0;
        apr_bucket_alloc_t *ba = apr_bucket_alloc_create(pool);
        apr_bucket_brigade *bb = apr_brigade_create(pool, ba);
        apr_bucket_brigade *tmpbb = apr_brigade_create(pool, ba);
        apr_table_t *hbt = apr_table_make(pool, 10);

        apr_brigade_insert_file(bb, fp, 0, fi.size, pool);

        do {
            hb_server_t *server;
            char buf[4096];
            apr_size_t bsize = sizeof(buf);
            const char *ip;

            apr_brigade_cleanup(tmpbb);

            if (APR_BRIGADE_EMPTY(bb)) {
                break;
            }

            rv = apr_brigade_split_line(tmpbb, bb,
                                        APR_BLOCK_READ, sizeof(buf));
            lineno++;

            if (rv) {
                return rv;
            }

            apr_brigade_flatten(tmpbb, buf, &bsize);

            if (bsize == 0) {
                break;
            }

            buf[bsize - 1] = 0;

            /* comment */
            if (buf[0] == '#') {
                continue;
            }

            /* line format: <IP> <query_string>\n */
            t = strchr(buf, ' ');
            if (!t) {
                continue;
            }

            ip = apr_pstrmemdup(pool, buf, t - buf);
            t++;

            server = apr_hash_get(servers, ip, APR_HASH_KEY_STRING);

            if (server == NULL) {
                server = apr_pcalloc(pool, sizeof(hb_server_t));
                server->ip = ip;
                server->port = 80;
                server->seen = -1;

                apr_hash_set(servers, server->ip, APR_HASH_KEY_STRING, server);
            }

            apr_table_clear(hbt);

            argstr_to_table(pool, apr_pstrdup(pool, t), hbt);

            if (apr_table_get(hbt, "busy")) {
                server->busy = atoi(apr_table_get(hbt, "busy"));
            }

            if (apr_table_get(hbt, "ready")) {
                server->ready = atoi(apr_table_get(hbt, "ready"));
            }

            if (apr_table_get(hbt, "lastseen")) {
                server->seen = atoi(apr_table_get(hbt, "lastseen"));
            }

            if (apr_table_get(hbt, "port")) {
                server->port = atoi(apr_table_get(hbt, "port"));
            }

            if (server->busy == 0 && server->ready != 0) {
                /* Server has zero threads active, but lots of them ready,
                 * it likely just started up, so lets /4 the number ready,
                 * to prevent us from completely flooding it with all new
                 * requests.
                 */
                server->ready = server->ready / 4;
            }

        } while (1);
    }

    return APR_SUCCESS;
}