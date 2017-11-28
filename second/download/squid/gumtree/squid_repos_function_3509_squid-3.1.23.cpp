void
clientOpenListenSockets(void)
{
    clientHttpConnectionsOpen();
#if USE_SSL

    clientHttpsConnectionsOpen();
#endif

    if (NHttpSockets < 1)
        fatal("Cannot open HTTP Port");
}