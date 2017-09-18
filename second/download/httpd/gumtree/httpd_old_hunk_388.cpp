     */ 
    if ((ta = table_alloc(n, &ta_errno, 
                          ssl_scache_shmht_malloc,  
                          ssl_scache_shmht_calloc, 
                          ssl_scache_shmht_realloc, 
                          ssl_scache_shmht_free, s )) == NULL) {
        ssl_log(s, SSL_LOG_ERROR,
                "Cannot allocate hash table in shared memory: %s",
                table_strerror(ta_errno));
        ssl_die();
    }

    table_attr(ta, TABLE_FLAG_AUTO_ADJUST|TABLE_FLAG_ADJUST_DOWN);
    table_set_data_alignment(ta, sizeof(char *));
    table_clear(ta);
    mc->tSessionCacheDataTable = ta;

    /*
     * Log the done work
     */
    ssl_log(s, SSL_LOG_INFO, 
            "Init: Created hash-table (%d buckets) "
            "in shared memory (%d bytes) for SSL session cache", n, avail);
    return;
}

void ssl_scache_shmht_kill(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);
