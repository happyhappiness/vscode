int
icpCheckUdpHit(StoreEntry * e, HttpRequest * request)
{
    if (e == NULL)
        return 0;

    if (!e->validToSend())
        return 0;

    if (Config.onoff.icp_hit_stale)
        return 1;

    if (refreshCheckICP(e, request))
        return 0;

    return 1;
}