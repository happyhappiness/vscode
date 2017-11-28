void
clientOpenListenSockets(void)
{
    clientHttpConnectionsOpen();
#if USE_OPENSSL
    clientHttpsConnectionsOpen();
#endif
    Ftp::StartListening();

    if (NHttpSockets < 1)
        fatal("No HTTP, HTTPS, or FTP ports configured");
}