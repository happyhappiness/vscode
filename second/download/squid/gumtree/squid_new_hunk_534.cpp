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

