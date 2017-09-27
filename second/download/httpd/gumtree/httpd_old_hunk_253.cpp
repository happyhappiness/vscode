    UCHAR ucaData[SSL_SESSION_MAX_DER];
    int nData;
    UCHAR *ucp;
    apr_status_t rv;

    /* streamline session data */
    if ((nData = i2d_SSL_SESSION(sess, NULL)) > sizeof(ucaData))
        return FALSE;
    ucp = ucaData;
    i2d_SSL_SESSION(sess, &ucp);

    /* be careful: do not try to store too much bytes in a DBM file! */
#ifdef PAIRMAX
    if ((idlen + nData) >= PAIRMAX)
        return FALSE;
#else
    if ((idlen + nData) >= 950 /* at least less than approx. 1KB */)
        return FALSE;
#endif

    /* create DBM key */
    dbmkey.dptr  = (char *)id;
    dbmkey.dsize = idlen;

    /* create DBM value */
    dbmval.dsize = sizeof(time_t) + nData;
    dbmval.dptr  = (char *)malloc(dbmval.dsize);
    if (dbmval.dptr == NULL)
        return FALSE;
    memcpy((char *)dbmval.dptr, &expiry, sizeof(time_t));
    memcpy((char *)dbmval.dptr+sizeof(time_t), ucaData, nData);

    /* and store it to the DBM file */
    ssl_mutex_on(s);
    if ((rv = apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
