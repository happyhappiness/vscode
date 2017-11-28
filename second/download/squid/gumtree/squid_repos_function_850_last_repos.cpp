peer_t
parseNeighborType(const char *s)
{
    if (!strcmp(s, "parent"))
        return PEER_PARENT;

    if (!strcmp(s, "neighbor"))
        return PEER_SIBLING;

    if (!strcmp(s, "neighbour"))
        return PEER_SIBLING;

    if (!strcmp(s, "sibling"))
        return PEER_SIBLING;

    if (!strcmp(s, "multicast"))
        return PEER_MULTICAST;

    debugs(15, DBG_CRITICAL, "WARNING: Unknown neighbor type: " << s);

    return PEER_SIBLING;
}