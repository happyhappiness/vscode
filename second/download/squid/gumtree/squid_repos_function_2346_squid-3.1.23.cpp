static int
ipcacheParse(ipcache_entry *i, rfc1035_rr * answers, int nr, const char *error_message)
{
    int k;
    int j = 0;
    int na = 0;
    int ttl = 0;
    const char *name = (const char *)i->hash.key;
    int cname_found = 0;

    i->expires = squid_curtime + Config.negativeDnsTtl;
    i->flags.negcached = 1;
    safe_free(i->addrs.in_addrs);
    assert(i->addrs.in_addrs == NULL);
    safe_free(i->addrs.bad_mask);
    assert(i->addrs.bad_mask == NULL);
    safe_free(i->error_message);
    assert(i->error_message == NULL);
    i->addrs.count = 0;

    if (nr < 0) {
        debugs(14, 3, "ipcacheParse: Lookup failed '" << error_message << "' for '" << (const char *)i->hash.key << "'");
        i->error_message = xstrdup(error_message);
        return -1;
    }

    if (nr == 0) {
        debugs(14, 3, "ipcacheParse: No DNS records in response to '" << name << "'");
        i->error_message = xstrdup("No DNS records");
        return -1;
    }

    assert(answers);

    for (k = 0; k < nr; k++) {

        if (Ip::EnableIpv6 && answers[k].type == RFC1035_TYPE_AAAA) {
            if (answers[k].rdlength != sizeof(struct in6_addr)) {
                debugs(14, 1, "ipcacheParse: Invalid IPv6 address in response to '" << name << "'");
                continue;
            }
            na++;
            IpcacheStats.rr_aaaa++;
            continue;
        }

        if (answers[k].type == RFC1035_TYPE_A) {
            if (answers[k].rdlength != sizeof(struct in_addr)) {
                debugs(14, 1, "ipcacheParse: Invalid IPv4 address in response to '" << name << "'");
                continue;
            }
            na++;
            IpcacheStats.rr_a++;
            continue;
        }

        /* With A and AAAA, the CNAME does not necessarily come with additional records to use. */
        if (answers[k].type == RFC1035_TYPE_CNAME) {
            cname_found=1;
            IpcacheStats.rr_cname++;

#if DNS_CNAME
            debugs(14, 5, "ipcacheParse: " << name << " CNAME " << answers[k].rdata << " (checking destination: " << i << ").");
            const ipcache_addrs *res = ipcache_gethostbyname(answers[k].rdata, 0);
            if (res) {
                na += res->count;
                debugs(14, 5, "ipcacheParse: CNAME " << answers[k].rdata << " already has " << res->count << " IPs cached.");
            } else {
                /* keep going on this, but flag the fact that we need to wait for a CNAME lookup to finish */
                debugs(14, 5, "ipcacheParse: CNAME " << answers[k].rdata << " has no IPs! Recursing.");
                ipcache_nbgethostbyname(answers[k].rdata, ipcacheHandleCnameRecurse, new generic_cbdata(i) );
                i->cname_wait++;
            }
#endif /* DNS_CNAME */

            continue;
        }

        // otherwise its an unknown RR. debug at level 9 since we usually want to ignore these and they are common.
        debugs(14, 9, HERE << "Unknown RR type received: type=" << answers[k].type << " starting at " << &(answers[k]) );
    }

#if DNS_CNAME
    if (na == 0 && i->cname_wait >0 ) {
        /* don't set any error message (yet). Allow recursion to do its work first. */
        IpcacheStats.cname_only++;
        return 0;
    }
#endif /* DNS_CNAME */

    if (na == 0) {
        debugs(14, 1, "ipcacheParse: No Address records in response to '" << name << "'");
        i->error_message = xstrdup("No Address records");
        if (cname_found)
            IpcacheStats.cname_only++;
        return 0;
    }

    i->addrs.in_addrs = (IpAddress *)xcalloc(na, sizeof(IpAddress));
    for (int l = 0; l < na; l++)
        i->addrs.in_addrs[l].SetEmpty(); // perform same init actions as constructor would.
    i->addrs.bad_mask = (unsigned char *)xcalloc(na, sizeof(unsigned char));

    for (j = 0, k = 0; k < nr; k++) {

        if (answers[k].type == RFC1035_TYPE_A) {
            if (answers[k].rdlength != sizeof(struct in_addr))
                continue;

            struct in_addr temp;
            xmemcpy(&temp, answers[k].rdata, sizeof(struct in_addr));
            i->addrs.in_addrs[j] = temp;

            debugs(14, 3, "ipcacheParse: " << name << " #" << j << " " << i->addrs.in_addrs[j]);
            j++;

        } else if (Ip::EnableIpv6 && answers[k].type == RFC1035_TYPE_AAAA) {
            if (answers[k].rdlength != sizeof(struct in6_addr))
                continue;

            struct in6_addr temp;
            xmemcpy(&temp, answers[k].rdata, sizeof(struct in6_addr));
            i->addrs.in_addrs[j] = temp;

            debugs(14, 3, "ipcacheParse: " << name << " #" << j << " " << i->addrs.in_addrs[j] );
            j++;
        }
#if DNS_CNAME
        else if (answers[k].type == RFC1035_TYPE_CNAME) {
            debugs(14, 3, "ipcacheParse: " << name << " #x CNAME " << answers[k].rdata);
            const ipcache_addrs *res = ipcache_gethostbyname(answers[k].rdata, 0);
            if (res) {
                /* NP: the results of *that* query need to be integrated in place of the CNAME */
                /* Ideally we should also integrate the min TTL of the above IPA's into ttl.   */
                for (int l = 0; l < res->count; l++, j++) {
                    i->addrs.in_addrs[j] = res->in_addrs[l];
                    debugs(14, 3, "ipcacheParse: " << name << " #" << j << " " << i->addrs.in_addrs[j] );
                }
            } else {
                debugs(14, 9, "ipcacheParse: " << answers[k].rdata << " (CNAME) waiting on A/AAAA records.");
            }
        }
#endif /* DNS_CNAME */

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

    i->flags.negcached = 0;

#if DNS_CNAME
    /* SPECIAL CASE: may get here IFF CNAME received with Additional records */
    /*               reurn  0/'wait for further details' value.              */
    /*               NP: 'No DNS Results' is a return -1 +msg                */
    if (i->cname_wait)
        return 0;
    else
#endif /* DNS_CNAME */
        return i->addrs.count;
}