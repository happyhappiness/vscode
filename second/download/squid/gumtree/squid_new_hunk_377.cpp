            p->connection_auth = 1;
        } else if (strcmp(token, "connection-auth=on") == 0) {
            p->connection_auth = 1;
        } else if (strcmp(token, "connection-auth=auto") == 0) {
            p->connection_auth = 2;
        } else {
            debugs(3, DBG_CRITICAL, "parse_peer: token='" << token << "'");
            self_destruct();
        }
    }

    if (peerFindByName(p->name))
        fatalf("ERROR: cache_peer %s specified twice\n", p->name);
