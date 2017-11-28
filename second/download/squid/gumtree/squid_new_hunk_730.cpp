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

