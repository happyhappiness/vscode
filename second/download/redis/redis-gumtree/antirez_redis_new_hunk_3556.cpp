        );
        unlockThreadedIO();
    }
    if (server.loading) {
        double perc;
        time_t eta, elapsed;
        off_t remaining_bytes = server.loading_total_bytes-
                                server.loading_loaded_bytes;

        perc = ((double)server.loading_loaded_bytes /
               server.loading_total_bytes) * 100;

        elapsed = time(NULL)-server.loading_start_time;
        if (elapsed == 0) {
            eta = 1; /* A fake 1 second figure if we don't have enough info */
        } else {
            eta = (elapsed*remaining_bytes)/server.loading_loaded_bytes;
        }

        info = sdscatprintf(info,
            "loading_start_time:%ld\r\n"
            "loading_total_bytes:%llu\r\n"
            "loading_loaded_bytes:%llu\r\n"
            "loading_loaded_perc:%.2f\r\n"
            "loading_eta_seconds:%ld\r\n"
            ,(unsigned long) server.loading_start_time,
            (unsigned long long) server.loading_total_bytes,
            (unsigned long long) server.loading_loaded_bytes,
            perc,
            eta
        );
    }
    for (j = 0; j < server.dbnum; j++) {
        long long keys, vkeys;

