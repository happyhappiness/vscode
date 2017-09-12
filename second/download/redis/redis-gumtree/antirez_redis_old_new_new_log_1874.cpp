line = sdscatprintf(sdsempty(),
                "sentinel notification-script %s %s",
                master->name, master->notification_script);