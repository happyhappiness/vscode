    if (strstr(r->element[2]->str,server.runid) != NULL) return;

    {
        int numtokens, port, removed, canfailover;
        /* Separator changed from ":" to "," in recent versions in order to
         * play well with IPv6 addresses. For now we make sure to parse both
         * correctly detecting if there is "," inside the string. */
        char *sep = strchr(r->element[2]->str,',') ? "," : ":";
        char **token = sdssplitlen(r->element[2]->str,
                                   r->element[2]->len,
                                   sep,1,&numtokens);
        sentinelRedisInstance *sentinel;

        if (numtokens == 4) {
            /* First, try to see if we already have this sentinel. */
            port = atoi(token[1]);
            canfailover = atoi(token[3]);
            sentinel = getSentinelRedisInstanceByAddrAndRunID(
                            ri->sentinels,token[0],port,token[2]);

            if (!sentinel) {
                /* If not, remove all the sentinels that have the same runid
                 * OR the same ip/port, because it's either a restart or a
                 * network topology change. */
                removed = removeMatchingSentinelsFromMaster(ri,token[0],port,
                                token[2]);
                if (removed) {
                    sentinelEvent(REDIS_NOTICE,"-dup-sentinel",ri,
                        "%@ #duplicate of %s:%d or %s",
                        token[0],port,token[2]);
                }

                /* Add the new sentinel. */
                sentinel = createSentinelRedisInstance(NULL,SRI_SENTINEL,
                                token[0],port,ri->quorum,ri);
                if (sentinel) {
                    sentinelEvent(REDIS_NOTICE,"+sentinel",sentinel,"%@");
                    /* The runid is NULL after a new instance creation and
                     * for Sentinels we don't have a later chance to fill it,
                     * so do it now. */
                    sentinel->runid = sdsnew(token[2]);
                }
            }

            /* Update the state of the Sentinel. */
            if (sentinel) {
                sentinel->last_hello_time = mstime();
                if (canfailover)
                    sentinel->flags |= SRI_CAN_FAILOVER;
                else
                    sentinel->flags &= ~SRI_CAN_FAILOVER;
            }
        }
        sdsfreesplitres(token,numtokens);
    }
}

void sentinelPingInstance(sentinelRedisInstance *ri) {
    mstime_t now = mstime();
    mstime_t info_period;
