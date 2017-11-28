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
