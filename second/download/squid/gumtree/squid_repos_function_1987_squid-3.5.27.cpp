void
peerDestroy(void *data)
{
    CachePeer *p = (CachePeer *)data;

    if (p == NULL)
        return;

    CachePeerDomainList *nl = NULL;

    for (CachePeerDomainList *l = p->peer_domain; l; l = nl) {
        nl = l->next;
        safe_free(l->domain);
        xfree(l);
    }

    safe_free(p->host);
    safe_free(p->name);
    safe_free(p->domain);
#if USE_CACHE_DIGESTS

    cbdataReferenceDone(p->digest);
#endif
}