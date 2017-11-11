static char *ssl_var_lookup_ssl(apr_pool_t *p, conn_rec *c, request_rec *r,
                                char *var)
{
    SSLConnRec *sslconn = myConnConfig(c);
    char *result;
    X509 *xs;
    STACK_OF(X509) *sk;
    SSL *ssl;

    result = NULL;

    ssl = sslconn->ssl;
    if (strlen(var) > 8 && strcEQn(var, "VERSION_", 8)) {
        result = ssl_var_lookup_ssl_version(p, var+8);
    }
    else if (ssl != NULL && strcEQ(var, "PROTOCOL")) {
        result = (char *)SSL_get_version(ssl);
    }
    else if (ssl != NULL && strcEQ(var, "SESSION_ID")) {
        char buf[SSL_SESSION_ID_STRING_LEN];
        SSL_SESSION *pSession = SSL_get_session(ssl);
        if (pSession) {
            unsigned char *id;
            unsigned int idlen;

#ifdef OPENSSL_NO_SSL_INTERN
            id = (unsigned char *)SSL_SESSION_get_id(pSession, &idlen);
#else
            id = pSession->session_id;
            idlen = pSession->session_id_length;
#endif

            result = apr_pstrdup(p, SSL_SESSION_id2sz(id, idlen,
                                                      buf, sizeof(buf)));
        }
    }
    else if(ssl != NULL && strcEQ(var, "SESSION_RESUMED")) {
        if (SSL_session_reused(ssl) == 1)
            result = "Resumed";
        else
            result = "Initial";
    }
    else if (ssl != NULL && strlen(var) >= 6 && strcEQn(var, "CIPHER", 6)) {
        result = ssl_var_lookup_ssl_cipher(p, c, var+6);
    }
    else if (ssl != NULL && strlen(var) > 18 && strcEQn(var, "CLIENT_CERT_CHAIN_", 18)) {
        sk = SSL_get_peer_cert_chain(ssl);
        result = ssl_var_lookup_ssl_cert_chain(p, sk, var+18);
    }
    else if (ssl != NULL && strcEQ(var, "CLIENT_VERIFY")) {
        result = ssl_var_lookup_ssl_cert_verify(p, c);
    }
    else if (ssl != NULL && strlen(var) > 7 && strcEQn(var, "CLIENT_", 7)) {
        if ((xs = SSL_get_peer_certificate(ssl)) != NULL) {
            result = ssl_var_lookup_ssl_cert(p, r, xs, var+7);
            X509_free(xs);
        }
    }
    else if (ssl != NULL && strlen(var) > 7 && strcEQn(var, "SERVER_", 7)) {
        if ((xs = SSL_get_certificate(ssl)) != NULL) {
            result = ssl_var_lookup_ssl_cert(p, r, xs, var+7);
            /* SSL_get_certificate is different from SSL_get_peer_certificate.
             * No need to X509_free(xs).
             */
        }
    }
    else if (ssl != NULL && strcEQ(var, "COMPRESS_METHOD")) {
        result = ssl_var_lookup_ssl_compress_meth(ssl);
    }
#ifdef HAVE_TLSEXT
    else if (ssl != NULL && strcEQ(var, "TLS_SNI")) {
        result = apr_pstrdup(p, SSL_get_servername(ssl,
                                                   TLSEXT_NAMETYPE_host_name));
    }
#endif
    else if (ssl != NULL && strcEQ(var, "SECURE_RENEG")) {
        int flag = 0;
#ifdef SSL_get_secure_renegotiation_support
        flag = SSL_get_secure_renegotiation_support(ssl);
#endif
        result = apr_pstrdup(p, flag ? "true" : "false");
    }
#ifdef HAVE_SRP
    else if (ssl != NULL && strcEQ(var, "SRP_USER")) {
        if ((result = SSL_get_srp_username(ssl)) != NULL) {
            result = apr_pstrdup(p, result);
        }
    }
    else if (ssl != NULL && strcEQ(var, "SRP_USERINFO")) {
        if ((result = SSL_get_srp_userinfo(ssl)) != NULL) {
            result = apr_pstrdup(p, result);
        }
    }
#endif

    return result;
}