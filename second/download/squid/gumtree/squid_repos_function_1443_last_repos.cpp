static int
peerDigestUseful(const PeerDigest * pd)
{
    /* TODO: we should calculate the prob of a false hit instead of bit util */
    const auto bit_util = pd->cd->usedMaskPercent();

    if (bit_util > 65.0) {
        debugs(72, DBG_CRITICAL, "Warning: " << pd->host <<
               " peer digest has too many bits on (" << bit_util << "%).");
        return 0;
    }

    return 1;
}