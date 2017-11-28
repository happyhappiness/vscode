        }
    }

    if (peerFindByName(p->name))
        fatalf("ERROR: cache_peer %s specified twice\n", p->name);

    if (p->weight < 1)
        p->weight = 1;

    if (p->connect_fail_limit < 1)
        p->connect_fail_limit = 10;

