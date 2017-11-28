static void
tunnelDelayedServerRead(void *data)
{
    if (!data)
        return;

    TunnelStateData *tunnel = static_cast<TunnelStateData*>(data);
    tunnel->server.readPending = NULL;
    static uint64_t counter=0;
    debugs(26, 7, "Server read(2) delayed " << ++counter << " times");
    tunnel->copyRead(tunnel->server, TunnelStateData::ReadServer);
}