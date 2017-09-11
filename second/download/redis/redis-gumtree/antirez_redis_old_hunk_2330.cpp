                (ustime()-start) > timelimit)
            {
                timelimit_exit = 1;
                return;
            }
        } while (expired > REDIS_EXPIRELOOKUPS_PER_CRON/4);
    }
}
