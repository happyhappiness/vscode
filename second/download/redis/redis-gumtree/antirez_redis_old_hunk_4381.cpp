        keys = dictSize(server.db[j].dict);
        vkeys = dictSize(server.db[j].expires);
        if (keys || vkeys) {
            info = sdscatprintf(info, "db%d: keys=%lld,expires=%lld\r\n",
                j, keys, vkeys);
        }
    }
