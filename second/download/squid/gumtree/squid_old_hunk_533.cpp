    if ((token = strtok(NULL, w_space)) == NULL)
        self_destruct();

    p->type = parseNeighborType(token);

    if (p->type == PEER_MULTICAST) {
        p->options.no_digest = 1;
        p->options.no_netdb_exchange = 1;
    }

    p->http_port = GetTcpService();

    if (!p->http_port)
        self_destruct();

    p->icp.port = GetUdpService();
    p->connection_auth = 2;    /* auto */

    while ((token = strtok(NULL, w_space))) {
        if (!strcasecmp(token, "proxy-only")) {
            p->options.proxy_only = 1;
        } else if (!strcasecmp(token, "no-query")) {
            p->options.no_query = 1;
        } else if (!strcasecmp(token, "background-ping")) {
            p->options.background_ping = 1;
        } else if (!strcasecmp(token, "no-digest")) {
            p->options.no_digest = 1;
        } else if (!strcasecmp(token, "no-tproxy")) {
            p->options.no_tproxy = 1;
        } else if (!strcasecmp(token, "multicast-responder")) {
            p->options.mcast_responder = 1;
#if PEER_MULTICAST_SIBLINGS
        } else if (!strcasecmp(token, "multicast-siblings")) {
            p->options.mcast_siblings = 1;
#endif
        } else if (!strncasecmp(token, "weight=", 7)) {
            p->weight = xatoi(token + 7);
        } else if (!strncasecmp(token, "basetime=", 9)) {
            p->basetime = xatoi(token + 9);
        } else if (!strcasecmp(token, "closest-only")) {
            p->options.closest_only = 1;
        } else if (!strncasecmp(token, "ttl=", 4)) {
            p->mcast.ttl = xatoi(token + 4);

            if (p->mcast.ttl < 0)
                p->mcast.ttl = 0;

            if (p->mcast.ttl > 128)
                p->mcast.ttl = 128;
        } else if (!strcasecmp(token, "default")) {
            p->options.default_parent = 1;
        } else if (!strcasecmp(token, "round-robin")) {
            p->options.roundrobin = 1;
        } else if (!strcasecmp(token, "weighted-round-robin")) {
            p->options.weighted_roundrobin = 1;
#if USE_HTCP
        } else if (!strcasecmp(token, "htcp")) {
            p->options.htcp = 1;
        } else if (!strncasecmp(token, "htcp=", 5) || !strncasecmp(token, "htcp-", 5)) {
            /* Note: The htcp- form is deprecated, replaced by htcp= */
            p->options.htcp = 1;
            char *tmp = xstrdup(token+5);
            char *mode, *nextmode;
            for (mode = nextmode = tmp; mode; mode = nextmode) {
                nextmode = strchr(mode, ',');
                if (nextmode) {
                    *nextmode = '\0';
                    ++nextmode;
                }
                if (!strcasecmp(mode, "no-clr")) {
                    if (p->options.htcp_only_clr)
                        fatalf("parse_peer: can't set htcp-no-clr and htcp-only-clr simultaneously");
                    p->options.htcp_no_clr = 1;
                } else if (!strcasecmp(mode, "no-purge-clr")) {
                    p->options.htcp_no_purge_clr = 1;
                } else if (!strcasecmp(mode, "only-clr")) {
                    if (p->options.htcp_no_clr)
                        fatalf("parse_peer: can't set htcp no-clr and only-clr simultaneously");
                    p->options.htcp_only_clr = 1;
                } else if (!strcasecmp(mode, "forward-clr")) {
                    p->options.htcp_forward_clr = 1;
                } else if (!strcasecmp(mode, "oldsquid")) {
                    p->options.htcp_oldsquid = 1;
                } else {
                    fatalf("invalid HTCP mode '%s'", mode);
                }
            }
            safe_free(tmp);
#endif
        } else if (!strcasecmp(token, "no-netdb-exchange")) {
            p->options.no_netdb_exchange = 1;

        } else if (!strcasecmp(token, "carp")) {
            if (p->type != PEER_PARENT)
                fatalf("parse_peer: non-parent carp peer %s/%d\n", p->host, p->http_port);

            p->options.carp = 1;
        } else if (!strncasecmp(token, "carp-key=", 9)) {
            if (p->options.carp != 1)
                fatalf("parse_peer: carp-key specified on non-carp peer %s/%d\n", p->host, p->http_port);
            p->options.carp_key.set=1;
            char *nextkey=token+strlen("carp-key="), *key=nextkey;
            for (; key; key = nextkey) {
                nextkey=strchr(key,',');
                if (nextkey) ++nextkey; // skip the comma, any
                if (0==strncasecmp(key,"scheme",6)) {
                    p->options.carp_key.scheme=1;
                } else if (0==strncasecmp(key,"host",4)) {
                    p->options.carp_key.host=1;
                } else if (0==strncasecmp(key,"port",4)) {
                    p->options.carp_key.port=1;
                } else if (0==strncasecmp(key,"path",4)) {
                    p->options.carp_key.path=1;
                } else if (0==strncasecmp(key,"params",6)) {
                    p->options.carp_key.params=1;
                } else {
                    fatalf("invalid carp-key '%s'",key);
                }
            }
        } else if (!strcasecmp(token, "userhash")) {
#if USE_AUTH
            if (p->type != PEER_PARENT)
                fatalf("parse_peer: non-parent userhash peer %s/%d\n", p->host, p->http_port);

            p->options.userhash = 1;
#else
            fatalf("parse_peer: userhash requires authentication. peer %s/%d\n", p->host, p->http_port);
#endif
        } else if (!strcasecmp(token, "sourcehash")) {
            if (p->type != PEER_PARENT)
                fatalf("parse_peer: non-parent sourcehash peer %s/%d\n", p->host, p->http_port);

            p->options.sourcehash = 1;

        } else if (!strcasecmp(token, "no-delay")) {
#if USE_DELAY_POOLS
            p->options.no_delay = 1;
#else
            debugs(0, DBG_CRITICAL, "WARNING: cache_peer option 'no-delay' requires --enable-delay-pools");
#endif
        } else if (!strncasecmp(token, "login=", 6)) {
            p->login = xstrdup(token + 6);
            rfc1738_unescape(p->login);
        } else if (!strncasecmp(token, "connect-timeout=", 16)) {
            p->connect_timeout = xatoi(token + 16);
        } else if (!strncasecmp(token, "connect-fail-limit=", 19)) {
            p->connect_fail_limit = xatoi(token + 19);
#if USE_CACHE_DIGESTS
        } else if (!strncasecmp(token, "digest-url=", 11)) {
            p->digest_url = xstrdup(token + 11);
#endif

        } else if (!strcasecmp(token, "allow-miss")) {
            p->options.allow_miss = 1;
        } else if (!strncasecmp(token, "max-conn=", 9)) {
            p->max_conn = xatoi(token + 9);
        } else if (!strcasecmp(token, "originserver")) {
            p->options.originserver = 1;
        } else if (!strncasecmp(token, "name=", 5)) {
            safe_free(p->name);

            if (token[5])
                p->name = xstrdup(token + 5);
        } else if (!strncasecmp(token, "forceddomain=", 13)) {
            safe_free(p->domain);

            if (token[13])
                p->domain = xstrdup(token + 13);

#if USE_SSL
