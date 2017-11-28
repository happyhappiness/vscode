}

void
clientOpenListenSockets(void)
{
    clientHttpConnectionsOpen();
    Ftp::StartListening();

    if (NHttpSockets < 1)
        fatal("No HTTP, HTTPS, or FTP ports configured");
}

void
clientConnectionsClose()
{
    for (AnyP::PortCfgPointer s = HttpPortList; s != NULL; s = s->next) {
        if (s->listenConn != NULL) {
            debugs(1, DBG_IMPORTANT, "Closing HTTP(S) port " << s->listenConn->local);
            s->listenConn->close();
            s->listenConn = NULL;
        }
    }

    Ftp::StopListening();

    // TODO see if we can drop HttpSockets array entirely */
    for (int i = 0; i < NHttpSockets; ++i) {
        HttpSockets[i] = -1;
    }
