    UCHAR ucaData[SSL_SESSION_MAX_DER];
    int nData;
    UCHAR *ucp;
    apr_status_t rv;

    /* streamline session data */
    if ((nData = i2d_SSL_SESSION(sess, NULL)) > sizeof(ucaData)) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "streamline session data size too large: %d > %d",
                 nData, sizeof(ucaData));
        return FALSE;
    }
    ucp = ucaData;
    i2d_SSL_SESSION(sess, &ucp);

    /* be careful: do not try to store too much bytes in a DBM file! */
#ifdef PAIRMAX
    if ((idlen + nData) >= PAIRMAX) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "data size too large for DBM session cache: %d >= %d",
                 (idlen + nData), PAIRMAX);
        return FALSE;
    }
#else
    if ((idlen + nData) >= 950 /* at least less than approx. 1KB */) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "data size too large for DBM session cache: %d >= %d",
                 (idlen + nData), 950);
        return FALSE;
    }
#endif

    /* create DBM key */
    dbmkey.dptr  = (char *)id;
    dbmkey.dsize = idlen;

    /* create DBM value */
    dbmval.dsize = sizeof(time_t) + nData;
    dbmval.dptr  = (char *)malloc(dbmval.dsize);
    if (dbmval.dptr == NULL) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "malloc error creating DBM value");
        return FALSE;
    }
    memcpy((char *)dbmval.dptr, &expiry, sizeof(time_t));
    memcpy((char *)dbmval.dptr+sizeof(time_t), ucaData, nData);

    /* and store it to the DBM file */
    ssl_mutex_on(s);
    if ((rv = apr_dbm_open(&dbm, mc->szSessionCacheDataFile,
