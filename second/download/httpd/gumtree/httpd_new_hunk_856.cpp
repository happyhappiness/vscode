
    ssl_io_filter_init(c, ssl);

    return APR_SUCCESS;
}

static const char *ssl_hook_http_method(const request_rec *r)
{
    SSLSrvConfigRec *sc = mySrvConfig(r->server);

    if (sc->enabled == FALSE) {
        return NULL;
