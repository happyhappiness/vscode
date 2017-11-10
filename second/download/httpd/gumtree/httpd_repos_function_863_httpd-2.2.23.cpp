static const char *ssl_hook_http_scheme(const request_rec *r)
{
    SSLSrvConfigRec *sc = mySrvConfig(r->server);

    if (sc->enabled == SSL_ENABLED_FALSE || sc->enabled == SSL_ENABLED_OPTIONAL) {
        return NULL;
    }

    return "https";
}