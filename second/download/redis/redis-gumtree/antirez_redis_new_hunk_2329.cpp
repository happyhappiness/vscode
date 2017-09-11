                num = REDIS_EXPIRELOOKUPS_PER_CRON;
            while (num--) {
                dictEntry *de;

                if ((de = dictGetRandomKey(db->expires)) == NULL) break;
                if (activeExpireCycleTryExpire(db,de,now)) expired++;
            }
            /* We can't block forever here even if there are many keys to
             * expire. So after a given amount of milliseconds return to the
