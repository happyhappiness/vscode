peer_t
parseNeighborType(const char *s)
{
    if (!strcasecmp(s, "parent"))
        return PEER_PARENT;

    if (!strcasecmp(s, "neighbor"))
        return PEER_SIBLING;

    if (!strcasecmp(s, "neighbour"))
        return PEER_SIBLING;

    if (!strcasecmp(s, "sibling"))
        return PEER_SIBLING;

    if (!strcasecmp(s, "multicast"))
        return PEER_MULTICAST;

    debugs(15, DBG_CRITICAL, "WARNING: Unknown neighbor type: " << s);

    return PEER_SIBLING;
}