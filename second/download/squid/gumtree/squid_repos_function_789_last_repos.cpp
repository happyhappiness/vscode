static void
parse_hostdomaintype(void)
{
    char *host = ConfigParser::NextToken();
    if (!host) {
        self_destruct();
        return;
    }

    char *type = ConfigParser::NextToken();
    if (!type) {
        self_destruct();
        return;
    }

    char *domain = nullptr;
    while ((domain = ConfigParser::NextToken())) {
        CachePeer *p = peerFindByName(host);
        if (!p) {
            debugs(15, DBG_CRITICAL, "" << cfg_filename << ", line " << config_lineno << ": No cache_peer '" << host << "'");
            return;
        }

        auto *l = static_cast<NeighborTypeDomainList *>(xcalloc(1, sizeof(NeighborTypeDomainList)));
        l->type = parseNeighborType(type);
        l->domain = xstrdup(domain);

        NeighborTypeDomainList **L = nullptr;
        for (L = &(p->typelist); *L; L = &((*L)->next));
        *L = l;
    }
}