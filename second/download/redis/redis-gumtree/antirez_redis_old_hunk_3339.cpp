    }
    info = sdscat(info,"\r\n");

    for (j = 0; j < server.dbnum; j++) {
        long long keys, vkeys;

