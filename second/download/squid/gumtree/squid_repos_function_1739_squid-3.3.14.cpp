static void
peerDigestSetCheck(PeerDigest * pd, time_t delay)
{
    eventAdd("peerDigestCheck", peerDigestCheck, pd, (double) delay, 1);
    pd->times.next_check = squid_curtime + delay;
    debugs(72, 3, "peerDigestSetCheck: will check peer " << pd->host << " in " << delay << " secs");
}