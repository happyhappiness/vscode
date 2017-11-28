                          neighborTypeStr(p),
                          p->http_port,
                          p->icp.port,
                          p->name);
        dump_peer_options(entry, p);

        if (p->access) {
            snprintf(xname, 128, "cache_peer_access %s", p->name);
            dump_acl_access(entry, xname, p->access);
        }

        for (t = p->typelist; t; t = t->next) {
