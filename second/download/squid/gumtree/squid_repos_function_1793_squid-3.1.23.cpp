peer *
peerFindByName(const char *name)
{
    peer *p = NULL;

    for (p = Config.peers; p; p = p->next) {
        if (!strcasecmp(name, p->name))
            break;
    }

    return p;
}