             * replied with a vote. */
            sdsfree(ri->leader);
            if ((long long)ri->leader_epoch != r->element[2]->integer)
                redisLog(REDIS_WARNING,
                    "%s voted for %s %llu", ri->name,
                    r->element[1]->str,
                    (unsigned long long) r->element[2]->integer);
