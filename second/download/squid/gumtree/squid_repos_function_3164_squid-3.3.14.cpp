static int
fqdncacheParse(fqdncache_entry *f, const rfc1035_rr * answers, int nr, const char *error_message)
{
    int k;
    int ttl = 0;
    const char *name = (const char *)f->hash.key;
    f->expires = squid_curtime + Config.negativeDnsTtl;
    f->flags.negcached = 1;

    if (nr < 0) {
        debugs(35, 3, "fqdncacheParse: Lookup of '" << name << "' failed (" << error_message << ")");
        f->error_message = xstrdup(error_message);
        return -1;
    }

    if (nr == 0) {
        debugs(35, 3, "fqdncacheParse: No DNS records for '" << name << "'");
        f->error_message = xstrdup("No DNS records");
        return 0;
    }

    debugs(35, 3, "fqdncacheParse: " << nr << " answers for '" << name << "'");
    assert(answers);

    for (k = 0; k < nr; ++k) {
        if (answers[k]._class != RFC1035_CLASS_IN)
            continue;

        if (answers[k].type == RFC1035_TYPE_PTR) {
            if (!answers[k].rdata[0]) {
                debugs(35, 2, "fqdncacheParse: blank PTR record for '" << name << "'");
                continue;
            }

            if (strchr(answers[k].rdata, ' ')) {
                debugs(35, 2, "fqdncacheParse: invalid PTR record '" << answers[k].rdata << "' for '" << name << "'");
                continue;
            }

            f->names[f->name_count] = xstrdup(answers[k].rdata);
            ++ f->name_count;
        } else if (answers[k].type != RFC1035_TYPE_CNAME)
            continue;

        if (ttl == 0 || (int) answers[k].ttl < ttl)
            ttl = answers[k].ttl;

        if (f->name_count >= FQDN_MAX_NAMES)
            break;
    }

    if (f->name_count == 0) {
        debugs(35, DBG_IMPORTANT, "fqdncacheParse: No PTR record for '" << name << "'");
        return 0;
    }

    if (ttl > Config.positiveDnsTtl)
        ttl = Config.positiveDnsTtl;

    if (ttl < Config.negativeDnsTtl)
        ttl = Config.negativeDnsTtl;

    f->expires = squid_curtime + ttl;

    f->flags.negcached = 0;

    return f->name_count;
}