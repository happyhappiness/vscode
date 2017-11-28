static void
tunnelDelayedClientRead(void *data)
{
    if (!data)
        return;

    TunnelStateData *tunnel = static_cast<TunnelStateData*>(data);
    tunnel->client.readPending = NULL;
    static uint64_t counter=0;
    debugs(26, 7, "Client read(2) delayed " << ++counter << " times");
    tunnel->copyRead(tunnel->client, TunnelStateData::ReadClient);
}