            {
                timelimit_exit = 1;
            }
#if 0
            expired_history_id = (expired_history_id+1) % EXPIRED_HISTORY_LEN;
            expired_history[expired_history_id] = expired;
            {
                int i;
                expired_perc_avg = 0;
                for (i = 0; i < EXPIRED_HISTORY_LEN; i++) {
                    expired_perc_avg += expired_history[i];
                }
                expired_perc_avg = (expired_perc_avg * 100) / (REDIS_EXPIRELOOKUPS_PER_CRON*EXPIRED_HISTORY_LEN);
                // printf("Expired AVG: %d\n", expired_perc_avg);
            }
#endif
            if (timelimit_exit) return;
        } while (expired > REDIS_EXPIRELOOKUPS_PER_CRON/4);
    }
