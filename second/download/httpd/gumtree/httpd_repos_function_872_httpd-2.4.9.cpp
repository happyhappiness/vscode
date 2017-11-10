int ssl_callback_NewSessionCacheEntry(SSL *ssl, SSL_SESSION *session)
{
    /* Get Apache context back through OpenSSL context */
    conn_rec *conn      = (conn_rec *)SSL_get_app_data(ssl);
    server_rec *s       = mySrvFromConn(conn);
    SSLSrvConfigRec *sc = mySrvConfig(s);
    long timeout        = sc->session_cache_timeout;
    BOOL rc;
    unsigned char *id;
    unsigned int idlen;

    /*
     * Set the timeout also for the internal OpenSSL cache, because this way
     * our inter-process cache is consulted only when it's really necessary.
     */
    SSL_set_timeout(session, timeout);

    /*
     * Store the SSL_SESSION in the inter-process cache with the
     * same expire time, so it expires automatically there, too.
     */
#ifdef OPENSSL_NO_SSL_INTERN
    id = (unsigned char *)SSL_SESSION_get_id(session, &idlen);
#else
    id = session->session_id;
    idlen = session->session_id_length;
#endif

    rc = ssl_scache_store(s, id, idlen,
                          apr_time_from_sec(SSL_SESSION_get_time(session)
                                          + timeout),
                          session, conn->pool);

    ssl_session_log(s, "SET", id, idlen,
                    rc == TRUE ? "OK" : "BAD",
                    "caching", timeout);

    /*
     * return 0 which means to OpenSSL that the session is still
     * valid and was not freed by us with SSL_SESSION_free().
     */
    return 0;
}