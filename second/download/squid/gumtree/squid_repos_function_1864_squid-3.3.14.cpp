CachePeer *
peerFindByName(const char *name)
{
    CachePeer *p = NULL;

    for (p = Config.peers; p; p = p->next) {
        if (!strcasecmp(name, p->name))
            break;
    }

    return p;
}