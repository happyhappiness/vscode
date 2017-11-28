static int
peerDigestUseful(const PeerDigest * pd)
{
    /* TODO: we should calculate the prob of a false hit instead of bit util */
    const int bit_util = cacheDigestBitUtil(pd->cd);

    if (bit_util > 65) {
        debugs(72, 0, "Warning: " << pd->host <<
               " peer digest has too many bits on (" << bit_util << "%%).");

        return 0;
    }

    return 1;
}