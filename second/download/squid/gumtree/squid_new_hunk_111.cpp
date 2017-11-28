
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
            debugs(1, 1, "Closing HTTP port " << s->listenConn->local);
            s->listenConn->close();
            s->listenConn = NULL;
        }
    }

#if USE_SSL
    for (AnyP::PortCfg *s = Config.Sockaddr.https; s; s = s->next) {
        if (s->listenConn != NULL) {
            debugs(1, 1, "Closing HTTPS port " << s->listenConn->local);
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
