static apr_status_t read_heartbeats(const char *path,
                                    apr_array_header_t *servers,
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
        apr_table_t *hbt = apr_table_make(pool, 10);
        char buf[4096];

        while (apr_file_gets(buf, sizeof(buf), fp) == APR_SUCCESS) {
            hb_server_t *server;
            const char *ip;
            lineno++;

            /* comment */
            if (buf[0] == '#') {
                continue;
            }
            
            
            /* line format: <IP> <query_string>\n */
            t = strchr(buf, ' ');
            if (!t) {
                continue;
            }
            
            ip = apr_pstrndup(pool, buf, t - buf);
            t++;
            server = apr_pcalloc(pool, sizeof(hb_server_t));
            server->ip = ip;
            server->port = 80;
            server->seen = -1;
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

            APR_ARRAY_PUSH(servers, hb_server_t *) = server;
        }
    }
    
    return APR_SUCCESS;
}