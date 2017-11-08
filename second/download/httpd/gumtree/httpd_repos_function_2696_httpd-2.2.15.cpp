static void mget_conn_result(int serverup,
                             int connup,
                             apr_status_t rv,
                             apr_memcache_t *mc,
                             apr_memcache_server_t *ms,
                             apr_memcache_conn_t *conn,
                             struct cache_server_query_t *server_query,
                             apr_hash_t *values,
                             apr_hash_t *server_queries)
{
    apr_int32_t j;
    apr_memcache_value_t* value;
    
    apr_hash_set(server_queries, &ms, sizeof(ms), NULL);

    if (connup) {
        ms_release_conn(ms, conn);
    } else {
        ms_bad_conn(ms, conn);

        if (!serverup) {
            apr_memcache_disable_server(mc, ms);
        }
    }
    
    for (j = 1; j < server_query->query_vec_count ; j+=2) {
        if (server_query->query_vec[j].iov_base) {
            value = apr_hash_get(values, server_query->query_vec[j].iov_base,
                                 strlen(server_query->query_vec[j].iov_base));
            
            if (value->status == APR_NOTFOUND) {
                value->status = rv;
            }
        }
    }
}