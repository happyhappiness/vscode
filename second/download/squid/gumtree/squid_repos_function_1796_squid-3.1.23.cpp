void
peerDestroy(void *data)
{
    peer *p = (peer *)data;

    struct _domain_ping *l = NULL;

    struct _domain_ping *nl = NULL;

    if (p == NULL)
        return;

    for (l = p->peer_domain; l; l = nl) {
        nl = l->next;
        safe_free(l->domain);
        safe_free(l);
    }

    safe_free(p->host);
    safe_free(p->name);
    safe_free(p->domain);
#if USE_CACHE_DIGESTS

    cbdataReferenceDone(p->digest);
#endif
}