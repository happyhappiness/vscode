            "role:%s\r\n",
            server.masterhost == NULL ? "master" : "slave");
        if (server.masterhost) {
            info = sdscatprintf(info,
                "master_host:%s\r\n"
                "master_port:%d\r\n"
