                                    server.loading_loaded_bytes;

            perc = ((double)server.loading_loaded_bytes /
                   (server.loading_total_bytes+1)) * 100;

            elapsed = time(NULL)-server.loading_start_time;
            if (elapsed == 0) {
                eta = 1; /* A fake 1 second figure if we don't have
                            enough info */
            } else {
                eta = (elapsed*remaining_bytes)/(server.loading_loaded_bytes+1);
            }

            info = sdscatprintf(info,
