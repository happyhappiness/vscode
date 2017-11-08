void ssl_callback_DelSessionCacheEntry(SSL_CTX *ctx,
                                       SSL_SESSION *session)
{
    server_rec *s;
    SSLSrvConfigRec *sc;
    unsigned char *id;
    unsigned int idlen;

    /*
     * Get Apache context back through OpenSSL context
     */
    if (!(s = (server_rec *)SSL_CTX_get_app_data(ctx))) {
        return; /* on server shutdown Apache is already gone */
    }

    sc = mySrvConfig(s);

    /*
     * Remove the SSL_SESSION from the inter-process cache
     */
#ifdef OPENSSL_NO_SSL_INTERN
    id = (unsigned char *)SSL_SESSION_get_id(session, &idlen);
#else
    id = session->session_id;
    idlen = session->session_id_length;
#endif

    /* TODO: Do we need a temp pool here, or are we always shutting down? */
    ssl_scache_remove(s, id, idlen, sc->mc->pPool);

    ssl_session_log(s, "REM", id, idlen,
                    "OK", "dead", 0);

    return;
}