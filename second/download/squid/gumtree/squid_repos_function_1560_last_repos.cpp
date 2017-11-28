static bool
peerProbeIsBusy(const CachePeer *p)
{
    if (p->testing_now > 0) {
        debugs(15, 8, "yes, probing " << p);
        return true;
    }
    if (squid_curtime - p->stats.last_connect_probe == 0) {
        debugs(15, 8, "yes, just probed " << p);
        return true;
    }
    return false;
}