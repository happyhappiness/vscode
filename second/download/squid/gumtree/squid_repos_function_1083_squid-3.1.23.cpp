static void
parse_hostdomain(void)
{
    char *host = NULL;
    char *domain = NULL;

    if (!(host = strtok(NULL, w_space)))
        self_destruct();

    while ((domain = strtok(NULL, list_sep))) {
        domain_ping *l = NULL;
        domain_ping **L = NULL;
        peer *p;

        if ((p = peerFindByName(host)) == NULL) {
            debugs(15, 0, "" << cfg_filename << ", line " << config_lineno << ": No cache_peer '" << host << "'");
            continue;
        }

        l = static_cast<domain_ping *>(xcalloc(1, sizeof(domain_ping)));
        l->do_ping = 1;

        if (*domain == '!') {	/* check for !.edu */
            l->do_ping = 0;
            domain++;
        }

        l->domain = xstrdup(domain);

        for (L = &(p->peer_domain); *L; L = &((*L)->next));
        *L = l;
    }
}