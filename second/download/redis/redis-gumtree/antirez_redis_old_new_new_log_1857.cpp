line = sdscatprintf(sdsempty(),
                "sentinel client-reconfig-script %s %s",
                master->name, master->client_reconfig_script);