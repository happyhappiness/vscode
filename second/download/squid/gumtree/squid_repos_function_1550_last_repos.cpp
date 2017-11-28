CachePeer *
peerFindByNameAndPort(const char *name, unsigned short port)
{
    CachePeer *p = NULL;

    for (p = Config.peers; p; p = p->next) {
        if (strcasecmp(name, p->name))
            continue;

        if (port != p->http_port)
            continue;

        break;
    }

    return p;
}