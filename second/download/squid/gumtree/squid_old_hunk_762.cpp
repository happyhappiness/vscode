}

void
clientOpenListenSockets(void)
{
    clientHttpConnectionsOpen();
#if USE_SSL
    clientHttpsConnectionsOpen();
#endif

    if (NHttpSockets < 1)
        fatal("No HTTP or HTTPS ports configured");
}

void
clientHttpConnectionsClose(void)
{
    for (AnyP::PortCfg *s = Config.Sockaddr.http; s; s = s->next) {
        if (s->listenConn != NULL) {
            debugs(1, DBG_IMPORTANT, "Closing HTTP port " << s->listenConn->local);
            s->listenConn->close();
            s->listenConn = NULL;
        }
    }

#if USE_SSL
    for (AnyP::PortCfg *s = Config.Sockaddr.https; s; s = s->next) {
        if (s->listenConn != NULL) {
            debugs(1, DBG_IMPORTANT, "Closing HTTPS port " << s->listenConn->local);
            s->listenConn->close();
            s->listenConn = NULL;
        }
    }
#endif

    // TODO see if we can drop HttpSockets array entirely */
    for (int i = 0; i < NHttpSockets; ++i) {
        HttpSockets[i] = -1;
    }

    NHttpSockets = 0;
}

int
varyEvaluateMatch(StoreEntry * entry, HttpRequest * request)
{
    const char *vary = request->vary_headers;
    int has_vary = entry->getReply()->header.has(HDR_VARY);
#if X_ACCELERATOR_VARY

    has_vary |=
        entry->getReply()->header.has(HDR_X_ACCELERATOR_VARY);
#endif

    if (!has_vary || !entry->mem_obj->vary_headers) {
        if (vary) {
            /* Oops... something odd is going on here.. */
            debugs(33, DBG_IMPORTANT, "varyEvaluateMatch: Oops. Not a Vary object on second attempt, '" <<
                   entry->mem_obj->url << "' '" << vary << "'");
            safe_free(request->vary_headers);
            return VARY_CANCEL;
        }

        if (!has_vary) {
            /* This is not a varying object */
            return VARY_NONE;
