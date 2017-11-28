acl_ip_data *
acl_ip_data::FactoryParse(const char *t)
{
    LOCAL_ARRAY(char, addr1, 256);
    LOCAL_ARRAY(char, addr2, 256);
    LOCAL_ARRAY(char, mask, 256);
    acl_ip_data *r = NULL;
    acl_ip_data **Q = NULL;
    Ip::Address temp;
    char c;
    unsigned int changed;
    acl_ip_data *q = new acl_ip_data;
    int iptype = AF_UNSPEC;

    debugs(28, 5, "aclIpParseIpData: " << t);

    /* Special ACL RHS "all" matches entire Internet */
    if (strcmp(t, "all") == 0) {
        debugs(28, 9, "aclIpParseIpData: magic 'all' found.");
        q->addr1.setAnyAddr();
        q->addr2.setEmpty();
        q->mask.setAnyAddr();
        return q;
    }

    /* Detect some old broken strings equivalent to 'all'.
     * treat them nicely. But be loud until its fixed.  */
    if (strcmp(t, "0/0") == 0 || strcmp(t, "0.0.0.0/0") == 0 || strcmp(t, "0.0.0.0/0.0.0.0") == 0 ||
            strcmp(t, "0.0.0.0-255.255.255.255") == 0 || strcmp(t, "0.0.0.0-0.0.0.0/0") == 0) {

        debugs(28,DBG_CRITICAL, "ERROR: '" << t << "' needs to be replaced by the term 'all'.");
        debugs(28,DBG_CRITICAL, "SECURITY NOTICE: Overriding config setting. Using 'all' instead.");
        q->addr1.setAnyAddr();
        q->addr2.setEmpty();
        q->mask.setAnyAddr();
        return q;
    }

    /* Special ACL RHS "ipv4" matches IPv4 Internet
     * A nod to IANA; we include the entire class space in case
     * they manage to find a way to recover and use it */
    if (strcmp(t, "ipv4") == 0) {
        q->mask.setNoAddr();
        q->mask.applyMask(0, AF_INET);
        return q;
    }

    /* Special ACL RHS "ipv6" matches IPv6-Unicast Internet */
    if (strcmp(t, "ipv6") == 0) {
        debugs(28, 9, "aclIpParseIpData: magic 'ipv6' found.");
        r = q; // save head of the list for result.

        /* 0000::/4 is a mix of localhost and obsolete IPv4-mapping space. Not valid outside this host. */

        /* Future global unicast space: 1000::/4 */
        q->addr1 = "1000::";
        q->mask.setNoAddr();
        q->mask.applyMask(4, AF_INET6);

        /* Current global unicast space: 2000::/4 = (2000::/4 - 3000::/4) */
        q->next = new acl_ip_data;
        q = q->next;
        q->addr1 = "2000::";
        q->mask.setNoAddr();
        q->mask.applyMask(3, AF_INET6);

        /* Future global unicast space: 4000::/2 = (4000::/4 - 7000::/4) */
        q->next = new acl_ip_data;
        q = q->next;
        q->addr1 = "4000::";
        q->mask.setNoAddr();
        q->mask.applyMask(2, AF_INET6);

        /* Future global unicast space: 8000::/2 = (8000::/4 - B000::/4) */
        q->next = new acl_ip_data;
        q = q->next;
        q->addr1 = "8000::";
        q->mask.setNoAddr();
        q->mask.applyMask(2, AF_INET6);

        /* Future global unicast space: C000::/3 = (C000::/4 - D000::/4) */
        q->next = new acl_ip_data;
        q = q->next;
        q->addr1 = "C000::";
        q->mask.setNoAddr();
        q->mask.applyMask(3, AF_INET6);

        /* Future global unicast space: E000::/4 */
        q->next = new acl_ip_data;
        q = q->next;
        q->addr1 = "E000::";
        q->mask.setNoAddr();
        q->mask.applyMask(4, AF_INET6);

        /* F000::/4 is mostly reserved non-unicast. With some exceptions ... */

        /* RFC 4193 Unique-Local unicast space: FC00::/7 */
        q->next = new acl_ip_data;
        q = q->next;
        q->addr1 = "FC00::";
        q->mask.setNoAddr();
        q->mask.applyMask(7, AF_INET6);

        /* Link-Local unicast space: FE80::/10 */
        q->next = new acl_ip_data;
        q = q->next;
        q->addr1 = "FE80::";
        q->mask.setNoAddr();
        q->mask.applyMask(10, AF_INET6);

        return r;
    }

// IPv4
    if (sscanf(t, SCAN_ACL1_4, addr1, addr2, mask) == 3) {
        debugs(28, 9, "aclIpParseIpData: '" << t << "' matched: SCAN1-v4: " << SCAN_ACL1_4);
        iptype=AF_INET;
    } else if (sscanf(t, SCAN_ACL2_4, addr1, addr2, &c) >= 2) {
        debugs(28, 9, "aclIpParseIpData: '" << t << "' matched: SCAN2-v4: " << SCAN_ACL2_4);
        mask[0] = '\0';
        iptype=AF_INET;
    } else if (sscanf(t, SCAN_ACL3_4, addr1, mask) == 2) {
        debugs(28, 9, "aclIpParseIpData: '" << t << "' matched: SCAN3-v4: " << SCAN_ACL3_4);
        addr2[0] = '\0';
        iptype=AF_INET;
    } else if (sscanf(t, SCAN_ACL4_4, addr1,&c) == 2) {
        debugs(28, 9, "aclIpParseIpData: '" << t << "' matched: SCAN4-v4: " << SCAN_ACL4_4);
        addr2[0] = '\0';
        mask[0] = '\0';
        iptype=AF_INET;

// IPv6
    } else if (sscanf(t, SCAN_ACL1_6, addr1, addr2, mask) == 3) {
        debugs(28, 9, "aclIpParseIpData: '" << t << "' matched: SCAN1-v6: " << SCAN_ACL1_6);
        iptype=AF_INET6;
    } else if (sscanf(t, SCAN_ACL2_6, addr1, addr2, &c) >= 2) {
        debugs(28, 9, "aclIpParseIpData: '" << t << "' matched: SCAN2-v6: " << SCAN_ACL2_6);
        mask[0] = '\0';
        iptype=AF_INET6;
    } else if (sscanf(t, SCAN_ACL3_6, addr1, mask) == 2) {
        debugs(28, 9, "aclIpParseIpData: '" << t << "' matched: SCAN3-v6: " << SCAN_ACL3_6);
        addr2[0] = '\0';
        iptype=AF_INET6;
    } else if (sscanf(t, SCAN_ACL4_6, addr1, mask) == 2) {
        debugs(28, 9, "aclIpParseIpData: '" << t << "' matched: SCAN4-v6: " << SCAN_ACL4_6);
        addr2[0] = '\0';
        iptype=AF_INET6;

// Neither
    } else if (sscanf(t, "%[^/]/%s", addr1, mask) == 2) {
        debugs(28, 9, "aclIpParseIpData: '" << t << "' matched: non-IP pattern: %[^/]/%s");
        addr2[0] = '\0';
    } else if (sscanf(t, "%s", addr1) == 1) {
        /*
         * Note, must use plain getaddrinfo() here because at startup
         * ipcache hasn't been initialized
         * TODO: offload this to one of the Ip::Address lookups.
         */

        debugs(28, 5, "aclIpParseIpData: Lookup Host/IP " << addr1);
        struct addrinfo *hp = NULL, *x = NULL;
        struct addrinfo hints;
        Ip::Address *prev_addr = NULL;

        memset(&hints, 0, sizeof(struct addrinfo));

        int errcode = getaddrinfo(addr1,NULL,&hints,&hp);
        if (hp == NULL) {
            delete q;
            if (strcmp(addr1, "::1") == 0) {
                debugs(28, DBG_IMPORTANT, "aclIpParseIpData: IPv6 has not been enabled in host DNS resolver.");
            } else {
                debugs(28, DBG_CRITICAL, "aclIpParseIpData: Bad host/IP: '" << addr1 <<
                       "' in '" << t << "', flags=" << hints.ai_flags <<
                       " : (" << errcode << ") " << gai_strerror(errcode) );
                self_destruct();
            }
            return NULL;
        }

        Q = &q;

        for (x = hp; x != NULL;) {
            if ((r = *Q) == NULL)
                r = *Q = new acl_ip_data;

            /* getaddrinfo given a host has a nasty tendency to return duplicate addr's */
            /* BUT sorted fortunately, so we can drop most of them easily */
            r->addr1 = *x;
            x = x->ai_next;
            if ( prev_addr && r->addr1 == *prev_addr) {
                debugs(28, 3, "aclIpParseIpData: Duplicate host/IP: '" << r->addr1 << "' dropped.");
                delete r;
                *Q = NULL;
                continue;
            } else
                prev_addr = &r->addr1;

            debugs(28, 3, "aclIpParseIpData: Located host/IP: '" << r->addr1 << "'");

            r->addr2.setAnyAddr();
            r->mask.setNoAddr();

            Q = &r->next;

            debugs(28, 3, "" << addr1 << " --> " << r->addr1 );
        }

        freeaddrinfo(hp);

        if (*Q != NULL) {
            debugs(28, DBG_CRITICAL, "aclIpParseIpData: Bad host/IP: '" << t << "'");
            self_destruct();
            return NULL;
        }

        return q;
    }

    /* ignore IPv6 addresses when built with IPv4-only */
    if ( iptype == AF_INET6 && !Ip::EnableIpv6) {
        debugs(28, DBG_IMPORTANT, "aclIpParseIpData: IPv6 has not been enabled.");
        delete q;
        return NULL;
    }

    /* Decode addr1 */
    if (!*addr1 || !(q->addr1 = addr1)) {
        debugs(28, DBG_CRITICAL, "aclIpParseIpData: unknown first address in '" << t << "'");
        delete q;
        self_destruct();
        return NULL;
    }

    /* Decode addr2 */
    if (!*addr2)
        q->addr2.setAnyAddr();
    else if (!(q->addr2=addr2) ) {
        debugs(28, DBG_CRITICAL, "aclIpParseIpData: unknown second address in '" << t << "'");
        delete q;
        self_destruct();
        return NULL;
    }

    /* Decode mask (NULL or empty means a exact host mask) */
    if (!DecodeMask(mask, q->mask, iptype)) {
        debugs(28, DBG_CRITICAL, "aclParseIpData: unknown netmask '" << mask << "' in '" << t << "'");
        delete q;
        self_destruct();
        return NULL;
    }

    changed = 0;
    changed += q->addr1.applyMask(q->mask);
    changed += q->addr2.applyMask(q->mask);

    if (changed)
        debugs(28, DBG_CRITICAL, "aclIpParseIpData: WARNING: Netmask masks away part of the specified IP in '" << t << "'");

    debugs(28,9, HERE << "Parsed: " << q->addr1 << "-" << q->addr2 << "/" << q->mask << "(/" << q->mask.cidr() <<")");

    /* 1.2.3.4/255.255.255.0  --> 1.2.3.0 */
    /* Same as IPv6 (not so trivial to depict) */
    return q;
}