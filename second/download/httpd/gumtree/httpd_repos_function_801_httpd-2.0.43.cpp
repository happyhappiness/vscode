void ssl_scache_shmht_expire(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);
    SSLSrvConfigRec *sc = mySrvConfig(s);
    static time_t tLast = 0;
    table_linear_t iterator;
    time_t tExpiresAt;
    void *vpKey;
    void *vpKeyThis;
    void *vpData;
    int nKey;
    int nKeyThis;
    int nData;
    int nElements = 0;
    int nDeleted = 0;
    int bDelete;
    int rc;
    time_t tNow;

    /*
     * make sure the expiration for still not-accessed session
     * cache entries is done only from time to time
     */
    tNow = time(NULL);
    if (tNow < tLast+sc->session_cache_timeout)
        return;
    tLast = tNow;

    ssl_mutex_on(s);
    if (table_first_r(mc->tSessionCacheDataTable, &iterator,
                      &vpKey, &nKey, &vpData, &nData) == TABLE_ERROR_NONE) {
        do {
            bDelete = FALSE;
            nElements++;
            if (nData < sizeof(time_t) || vpData == NULL)
                bDelete = TRUE;
            else {
                memcpy(&tExpiresAt, vpData, sizeof(time_t));
                /* 
                 * XXX : Force the record to be cleaned up. TBD (Madhu)
                 * tExpiresAt = tNow;
                 */
                if (tExpiresAt <= tNow)
                   bDelete = TRUE;
            }
            vpKeyThis = vpKey;
            nKeyThis  = nKey;
            rc = table_next_r(mc->tSessionCacheDataTable, &iterator,
                              &vpKey, &nKey, &vpData, &nData);
            if (bDelete) {
                table_delete(mc->tSessionCacheDataTable,
                             vpKeyThis, nKeyThis, NULL, NULL);
                nDeleted++;
            }
        } while (rc == TABLE_ERROR_NONE); 
        /* (vpKeyThis != vpKey) && (nKeyThis != nKey) */
    }
    ssl_mutex_off(s);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Inter-Process Session Cache (SHMHT) Expiry: "
                 "old: %d, new: %d, removed: %d",
                 nElements, nElements-nDeleted, nDeleted);
    return;
}