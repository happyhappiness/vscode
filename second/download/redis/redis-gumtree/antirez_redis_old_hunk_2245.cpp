            char payload[REDIS_IP_STR_LEN+1024];
            sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ?
                                             ri : ri->master;

            snprintf(payload,sizeof(payload),
                "%s,%d,%s,%d,%llu," /* Info about this sentinel. */
