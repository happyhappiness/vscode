static void
parse_peer(CachePeer ** head)
{
    char *host_str = ConfigParser::NextToken();
    if (!host_str) {
        self_destruct();
        return;
    }

    char *token = ConfigParser::NextToken();
    if (!token) {
        self_destruct();
        return;
    }

    CachePeer *p = new CachePeer;
    p->host = xstrdup(host_str);
    p->name = xstrdup(host_str);
    p->type = parseNeighborType(token);

    if (p->type == PEER_MULTICAST) {
        p->options.no_digest = true;
        p->options.no_netdb_exchange = true;
    }

    p->http_port = GetTcpService();

    if (!p->http_port) {
        delete p;
        self_destruct();
        return;
    }

    p->icp.port = GetUdpService();

    while ((token = ConfigParser::NextToken())) {
        if (!strcmp(token, "proxy-only")) {
            p->options.proxy_only = true;
        } else if (!strcmp(token, "no-query")) {
            p->options.no_query = true;
        } else if (!strcmp(token, "background-ping")) {
            p->options.background_ping = true;
        } else if (!strcmp(token, "no-digest")) {
            p->options.no_digest = true;
        } else if (!strcmp(token, "no-tproxy")) {
            p->options.no_tproxy = true;
        } else if (!strcmp(token, "multicast-responder")) {
            p->options.mcast_responder = true;
#if PEER_MULTICAST_SIBLINGS
        } else if (!strcmp(token, "multicast-siblings")) {
            p->options.mcast_siblings = true;
#endif
        } else if (!strncmp(token, "weight=", 7)) {
            p->weight = xatoi(token + 7);
        } else if (!strncmp(token, "basetime=", 9)) {
            p->basetime = xatoi(token + 9);
        } else if (!strcmp(token, "closest-only")) {
            p->options.closest_only = true;
        } else if (!strncmp(token, "ttl=", 4)) {
            p->mcast.ttl = xatoi(token + 4);

            if (p->mcast.ttl < 0)
                p->mcast.ttl = 0;

            if (p->mcast.ttl > 128)
                p->mcast.ttl = 128;
        } else if (!strcmp(token, "default")) {
            p->options.default_parent = true;
        } else if (!strcmp(token, "round-robin")) {
            p->options.roundrobin = true;
        } else if (!strcmp(token, "weighted-round-robin")) {
            p->options.weighted_roundrobin = true;
#if USE_HTCP
        } else if (!strcmp(token, "htcp")) {
            p->options.htcp = true;
        } else if (!strncmp(token, "htcp=", 5) || !strncmp(token, "htcp-", 5)) {
            /* Note: The htcp- form is deprecated, replaced by htcp= */
            p->options.htcp = true;
            char *tmp = xstrdup(token+5);
            char *mode, *nextmode;
            for (mode = nextmode = tmp; mode; mode = nextmode) {
                nextmode = strchr(mode, ',');
                if (nextmode) {
                    *nextmode = '\0';
                    ++nextmode;
                }
                if (!strcmp(mode, "no-clr")) {
                    if (p->options.htcp_only_clr)
                        fatalf("parse_peer: can't set htcp-no-clr and htcp-only-clr simultaneously");
                    p->options.htcp_no_clr = true;
                } else if (!strcmp(mode, "no-purge-clr")) {
                    p->options.htcp_no_purge_clr = true;
                } else if (!strcmp(mode, "only-clr")) {
                    if (p->options.htcp_no_clr)
                        fatalf("parse_peer: can't set htcp no-clr and only-clr simultaneously");
                    p->options.htcp_only_clr = true;
                } else if (!strcmp(mode, "forward-clr")) {
                    p->options.htcp_forward_clr = true;
                } else if (!strcmp(mode, "oldsquid")) {
                    p->options.htcp_oldsquid = true;
                } else {
                    fatalf("invalid HTCP mode '%s'", mode);
                }
            }
            safe_free(tmp);
#endif
        } else if (!strcmp(token, "no-netdb-exchange")) {
            p->options.no_netdb_exchange = true;

        } else if (!strcmp(token, "carp")) {
            if (p->type != PEER_PARENT)
                fatalf("parse_peer: non-parent carp peer %s/%d\n", p->host, p->http_port);

            p->options.carp = true;
        } else if (!strncmp(token, "carp-key=", 9)) {
            if (p->options.carp != true)
                fatalf("parse_peer: carp-key specified on non-carp peer %s/%d\n", p->host, p->http_port);
            p->options.carp_key.set = true;
            char *nextkey=token+strlen("carp-key="), *key=nextkey;
            for (; key; key = nextkey) {
                nextkey=strchr(key,',');
                if (nextkey) ++nextkey; // skip the comma, any
                if (0==strncmp(key,"scheme",6)) {
                    p->options.carp_key.scheme = true;
                } else if (0==strncmp(key,"host",4)) {
                    p->options.carp_key.host = true;
                } else if (0==strncmp(key,"port",4)) {
                    p->options.carp_key.port = true;
                } else if (0==strncmp(key,"path",4)) {
                    p->options.carp_key.path = true;
                } else if (0==strncmp(key,"params",6)) {
                    p->options.carp_key.params = true;
                } else {
                    fatalf("invalid carp-key '%s'",key);
                }
            }
        } else if (!strcmp(token, "userhash")) {
#if USE_AUTH
            if (p->type != PEER_PARENT)
                fatalf("parse_peer: non-parent userhash peer %s/%d\n", p->host, p->http_port);

            p->options.userhash = true;
#else
            fatalf("parse_peer: userhash requires authentication. peer %s/%d\n", p->host, p->http_port);
#endif
        } else if (!strcmp(token, "sourcehash")) {
            if (p->type != PEER_PARENT)
                fatalf("parse_peer: non-parent sourcehash peer %s/%d\n", p->host, p->http_port);

            p->options.sourcehash = true;

        } else if (!strcmp(token, "no-delay")) {
#if USE_DELAY_POOLS
            p->options.no_delay = true;
#else
            debugs(0, DBG_CRITICAL, "WARNING: cache_peer option 'no-delay' requires --enable-delay-pools");
#endif
        } else if (!strncmp(token, "login=", 6)) {
            p->login = xstrdup(token + 6);
            rfc1738_unescape(p->login);
        } else if (!strcmp(token, "auth-no-keytab")) {
            p->options.auth_no_keytab = 1;
        } else if (!strncmp(token, "connect-timeout=", 16)) {
            p->connect_timeout_raw = xatoi(token + 16);
        } else if (!strncmp(token, "connect-fail-limit=", 19)) {
            p->connect_fail_limit = xatoi(token + 19);
#if USE_CACHE_DIGESTS
        } else if (!strncmp(token, "digest-url=", 11)) {
            p->digest_url = xstrdup(token + 11);
#endif

        } else if (!strcmp(token, "allow-miss")) {
            p->options.allow_miss = true;
        } else if (!strncmp(token, "max-conn=", 9)) {
            p->max_conn = xatoi(token + 9);
        } else if (!strncmp(token, "standby=", 8)) {
            p->standby.limit = xatoi(token + 8);
        } else if (!strcmp(token, "originserver")) {
            p->options.originserver = true;
        } else if (!strncmp(token, "name=", 5)) {
            safe_free(p->name);

            if (token[5])
                p->name = xstrdup(token + 5);
        } else if (!strncmp(token, "forceddomain=", 13)) {
            safe_free(p->domain);
            if (token[13])
                p->domain = xstrdup(token + 13);

        } else if (strncmp(token, "ssl", 3) == 0) {
#if !USE_OPENSSL
            debugs(0, DBG_CRITICAL, "WARNING: cache_peer option '" << token << "' requires --with-openssl");
#else
            p->secure.parse(token+3);
#endif
        } else if (strncmp(token, "tls-", 4) == 0) {
            p->secure.parse(token+4);
        } else if (strncmp(token, "tls", 3) == 0) {
            p->secure.parse(token+3);
        } else if (strcmp(token, "front-end-https") == 0) {
            p->front_end_https = 1;
        } else if (strcmp(token, "front-end-https=on") == 0) {
            p->front_end_https = 1;
        } else if (strcmp(token, "front-end-https=auto") == 0) {
            p->front_end_https = 2;
        } else if (strcmp(token, "connection-auth=off") == 0) {
            p->connection_auth = 0;
        } else if (strcmp(token, "connection-auth") == 0) {
            p->connection_auth = 1;
        } else if (strcmp(token, "connection-auth=on") == 0) {
            p->connection_auth = 1;
        } else if (strcmp(token, "connection-auth=auto") == 0) {
            p->connection_auth = 2;
        } else if (token[0] == '#') {
            // start of a text comment. stop reading this line.
            break;
        } else {
            debugs(3, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: Ignoring unknown cache_peer option '" << token << "'");
        }
    }

    if (peerFindByName(p->name))
        fatalf("ERROR: cache_peer %s specified twice\n", p->name);

    if (p->max_conn > 0 && p->max_conn < p->standby.limit)
        fatalf("ERROR: cache_peer %s max-conn=%d is lower than its standby=%d\n", p->host, p->max_conn, p->standby.limit);

    if (p->weight < 1)
        p->weight = 1;

    if (p->connect_fail_limit < 1)
        p->connect_fail_limit = 10;

#if USE_CACHE_DIGESTS

    if (!p->options.no_digest) {
        /* XXX This looks odd.. who has the original pointer
         * then?
         */
        PeerDigest *pd = peerDigestCreate(p);
        p->digest = cbdataReference(pd);
    }

#endif

    p->index =  ++Config.npeers;

    while (*head != NULL)
        head = &(*head)->next;

    *head = p;

    peerClearRRStart();
}