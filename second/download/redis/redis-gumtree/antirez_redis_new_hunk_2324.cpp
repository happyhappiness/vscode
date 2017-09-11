            {
                timelimit_exit = 1;
            }
            if (timelimit_exit) return;
        } while (expired > REDIS_EXPIRELOOKUPS_PER_CRON/4);
    }
