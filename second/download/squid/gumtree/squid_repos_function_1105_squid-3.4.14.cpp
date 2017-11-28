static void
parse_hostdomain(void)
{
    char *host = NULL;
    char *domain = NULL;

    if (!(host = strtok(NULL, w_space)))
        self_destruct();

    while ((domain = strtok(NULL, list_sep))) {
        CachePeerDomainList *l = NULL;
        CachePeerDomainList **L = NULL;
        CachePeer *p;

        if ((p = peerFindByName(host)) == NULL) {
            debugs(15, DBG_CRITICAL, "" << cfg_filename << ", line " << config_lineno << ": No cache_peer '" << host << "'");
            continue;
        }

        l = static_cast<CachePeerDomainList *>(xcalloc(1, sizeof(CachePeerDomainList)));
        l->do_ping = true;

        if (*domain == '!') {	/* check for !.edu */
            l->do_ping = false;
            ++domain;
        }

        l->domain = xstrdup(domain);

        for (L = &(p->peer_domain); *L; L = &((*L)->next));
        *L = l;
    }
}