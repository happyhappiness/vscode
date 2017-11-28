void
clientOpenListenSockets(void)
{
    clientHttpConnectionsOpen();
    Ftp::StartListening();

    if (NHttpSockets < 1)
        fatal("No HTTP, HTTPS, or FTP ports configured");
}