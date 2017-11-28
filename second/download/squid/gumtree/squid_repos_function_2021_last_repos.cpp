static void
ipcacheParse(ipcache_entry *i, const rfc1035_rr * answers, int nr, const char *error_message)
{
    int k;
    int j = 0;
    int na = 0;
    int ttl = 0;
    const char *name = (const char *)i->hash.key;
    int cname_found = 0;

    i->expires = squid_curtime + Config.negativeDnsTtl;
    i->flags.negcached = true;
    safe_free(i->addrs.in_addrs);
    assert(i->addrs.in_addrs == NULL);
    safe_free(i->addrs.bad_mask);
    assert(i->addrs.bad_mask == NULL);
    safe_free(i->error_message);
    assert(i->error_message == NULL);
    i->addrs.count = 0;

    if (nr < 0) {
        debugs(14, 3, "Lookup failed '" << error_message << "' for '" << (const char *)i->hash.key << "'");
        i->error_message = xstrdup(error_message);
        return;
    }

    if (nr == 0) {
        debugs(14, 3, "No DNS records in response to '" << name << "'");
        i->error_message = xstrdup("No DNS records");
        return;
    }

    debugs(14, 3, nr << " answers for '" << name << "'");
    assert(answers);

    for (k = 0; k < nr; ++k) {

        if (Ip::EnableIpv6 && answers[k].type == RFC1035_TYPE_AAAA) {
            if (answers[k].rdlength != sizeof(struct in6_addr)) {
                debugs(14, DBG_IMPORTANT, MYNAME << "Invalid IPv6 address in response to '" << name << "'");
                continue;
            }
            ++na;
            ++IpcacheStats.rr_aaaa;
            continue;
        }

        if (answers[k].type == RFC1035_TYPE_A) {
            if (answers[k].rdlength != sizeof(struct in_addr)) {
                debugs(14, DBG_IMPORTANT, MYNAME << "Invalid IPv4 address in response to '" << name << "'");
                continue;
            }
            ++na;
            ++IpcacheStats.rr_a;
            continue;
        }

        /* With A and AAAA, the CNAME does not necessarily come with additional records to use. */
        if (answers[k].type == RFC1035_TYPE_CNAME) {
            cname_found=1;
            ++IpcacheStats.rr_cname;
            continue;
        }

        // otherwise its an unknown RR. debug at level 9 since we usually want to ignore these and they are common.
        debugs(14, 9, "Unknown RR type received: type=" << answers[k].type << " starting at " << &(answers[k]) );
    }
    if (na == 0) {
        debugs(14, DBG_IMPORTANT, MYNAME << "No Address records in response to '" << name << "'");
        i->error_message = xstrdup("No Address records");
        if (cname_found)
            ++IpcacheStats.cname_only;
        return;
    }

    i->addrs.in_addrs = static_cast<Ip::Address *>(xcalloc(na, sizeof(Ip::Address)));
    for (int l = 0; l < na; ++l)
        i->addrs.in_addrs[l].setEmpty(); // perform same init actions as constructor would.
    i->addrs.bad_mask = (unsigned char *)xcalloc(na, sizeof(unsigned char));

    for (j = 0, k = 0; k < nr; ++k) {

        if (answers[k].type == RFC1035_TYPE_A) {
            if (answers[k].rdlength != sizeof(struct in_addr))
                continue;

            struct in_addr temp;
            memcpy(&temp, answers[k].rdata, sizeof(struct in_addr));
            i->addrs.in_addrs[j] = temp;

            debugs(14, 3, name << " #" << j << " " << i->addrs.in_addrs[j]);
            ++j;

        } else if (Ip::EnableIpv6 && answers[k].type == RFC1035_TYPE_AAAA) {
            if (answers[k].rdlength != sizeof(struct in6_addr))
                continue;

            struct in6_addr temp;
            memcpy(&temp, answers[k].rdata, sizeof(struct in6_addr));
            i->addrs.in_addrs[j] = temp;

            debugs(14, 3, name << " #" << j << " " << i->addrs.in_addrs[j] );
            ++j;
        }
        if (ttl == 0 || (int) answers[k].ttl < ttl)
            ttl = answers[k].ttl;
    }

    assert(j == na);

    if (na < 256)
        i->addrs.count = (unsigned char) na;
    else
        i->addrs.count = 255;

    if (ttl > Config.positiveDnsTtl)
        ttl = Config.positiveDnsTtl;

    if (ttl < Config.negativeDnsTtl)
        ttl = Config.negativeDnsTtl;

    i->expires = squid_curtime + ttl;

    i->flags.negcached = false;
}