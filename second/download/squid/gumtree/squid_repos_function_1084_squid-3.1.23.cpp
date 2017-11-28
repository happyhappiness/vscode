static void
parse_hostdomaintype(void)
{
    char *host = NULL;
    char *type = NULL;
    char *domain = NULL;

    if (!(host = strtok(NULL, w_space)))
        self_destruct();

    if (!(type = strtok(NULL, w_space)))
        self_destruct();

    while ((domain = strtok(NULL, list_sep))) {
        domain_type *l = NULL;
        domain_type **L = NULL;
        peer *p;

        if ((p = peerFindByName(host)) == NULL) {
            debugs(15, 0, "" << cfg_filename << ", line " << config_lineno << ": No cache_peer '" << host << "'");
            return;
        }

        l = static_cast<domain_type *>(xcalloc(1, sizeof(domain_type)));
        l->type = parseNeighborType(type);
        l->domain = xstrdup(domain);

        for (L = &(p->typelist); *L; L = &((*L)->next));
        *L = l;
    }
}