void ssl_scache_shmht_status(server_rec *s, apr_pool_t *p, void (*func)(char *, void *), void *arg)
{
    SSLModConfigRec *mc = myModConfig(s);
    void *vpKey;
    void *vpData;
    int nKey;
    int nData;
    int nElem;
    int nSize;
    int nAverage;

    nElem = 0;
    nSize = 0;
    ssl_mutex_on(s);
    if (table_first(mc->tSessionCacheDataTable,
                    &vpKey, &nKey, &vpData, &nData) == TABLE_ERROR_NONE) {
        do {
            if (vpKey == NULL || vpData == NULL)
                continue;
            nElem += 1;
            nSize += nData;
        } while (table_next(mc->tSessionCacheDataTable,
                        &vpKey, &nKey, &vpData, &nData) == TABLE_ERROR_NONE);
    }
    ssl_mutex_off(s);
    if (nSize > 0 && nElem > 0)
        nAverage = nSize / nElem;
    else
        nAverage = 0;
    func(apr_psprintf(p, "cache type: <b>SHMHT</b>, maximum size: <b>%d</b> bytes<br>", mc->nSessionCacheDataSize), arg);
    func(apr_psprintf(p, "current sessions: <b>%d</b>, current size: <b>%d</b> bytes<br>", nElem, nSize), arg);
    func(apr_psprintf(p, "average session size: <b>%d</b> bytes<br>", nAverage), arg);
    return;
}