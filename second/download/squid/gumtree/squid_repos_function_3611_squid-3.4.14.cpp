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