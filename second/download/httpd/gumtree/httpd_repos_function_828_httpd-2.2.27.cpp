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
    id = SSL_SESSION_get_session_id(session);
    idlen = SSL_SESSION_get_session_id_length(session);

    ssl_scache_remove(s, id, idlen);

    ssl_session_log(s, "REM", id, idlen,
                    "OK", "dead", 0);

    return;
}