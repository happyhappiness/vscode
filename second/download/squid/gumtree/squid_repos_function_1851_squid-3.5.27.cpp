static void
peerDigestDisable(PeerDigest * pd)
{
    debugs(72, 2, "peerDigestDisable: peer " << pd->host.buf() << " disabled for good");
    pd->times.disabled = squid_curtime;
    pd->times.next_check = -1;  /* never */
    pd->flags.usable = 0;

    if (pd->cd) {
        cacheDigestDestroy(pd->cd);
        pd->cd = NULL;
    }

    /* we do not destroy the pd itself to preserve its "history" and stats */
}