void
hierarchyNote(HierarchyLogEntry * hl,
              hier_code code,
              const char *cache_peer)
{
    assert(hl != NULL);
    hl->code = code;
    xstrncpy(hl->host, cache_peer, SQUIDHOSTNAMELEN);
}