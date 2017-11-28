static void
dump_peer(StoreEntry * entry, const char *name, peer * p)
{
    domain_ping *d;
    domain_type *t;
    LOCAL_ARRAY(char, xname, 128);

    while (p != NULL) {
        storeAppendPrintf(entry, "%s %s %s %d %d name=%s",
                          name,
                          p->host,
                          neighborTypeStr(p),
                          p->http_port,
                          p->icp.port,
                          p->name);
        dump_peer_options(entry, p);

        for (d = p->peer_domain; d; d = d->next) {
            storeAppendPrintf(entry, "cache_peer_domain %s %s%s\n",
                              p->host,
                              d->do_ping ? null_string : "!",
                              d->domain);
        }

        if (p->access) {
            snprintf(xname, 128, "cache_peer_access %s", p->name);
            dump_acl_access(entry, xname, p->access);
        }

        for (t = p->typelist; t; t = t->next) {
            storeAppendPrintf(entry, "neighbor_type_domain %s %s %s\n",
                              p->host,
                              peer_type_str(t->type),
                              t->domain);
        }

        p = p->next;
    }
}