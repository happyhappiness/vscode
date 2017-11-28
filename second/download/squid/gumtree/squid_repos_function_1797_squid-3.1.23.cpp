void
peerNoteDigestGone(peer * p)
{
#if USE_CACHE_DIGESTS
    cbdataReferenceDone(p->digest);
#endif
}