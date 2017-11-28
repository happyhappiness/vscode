void
peerNoteDigestGone(CachePeer * p)
{
#if USE_CACHE_DIGESTS
    cbdataReferenceDone(p->digest);
#endif
}