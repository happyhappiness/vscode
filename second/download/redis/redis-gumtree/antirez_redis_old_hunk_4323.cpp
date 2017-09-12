            server.master ? ((int)(time(NULL)-server.master->lastinteraction)) : -1
        );
    }
    for (j = 0; j < server.dbnum; j++) {
        long long keys, vkeys;

