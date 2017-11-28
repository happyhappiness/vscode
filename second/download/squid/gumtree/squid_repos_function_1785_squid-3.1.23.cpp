void
peerNoteDigestLookup(HttpRequest * request, peer * p, lookup_t lookup)
{
#if USE_CACHE_DIGESTS

    if (p)
        strncpy(request->hier.cd_host, p->host, sizeof(request->hier.cd_host));
    else
        *request->hier.cd_host = '\0';

    request->hier.cd_lookup = lookup;

    debugs(15, 4, "peerNoteDigestLookup: peer " <<
           (p ? p->host : "<none>") << ", lookup: " <<
           lookup_t_str[lookup]  );

#endif
}