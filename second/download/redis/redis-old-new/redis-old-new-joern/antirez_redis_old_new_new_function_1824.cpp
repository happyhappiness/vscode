void sentinelSetCommand(redisClient *c) {
    sentinelRedisInstance *ri;
    int j, changes = 0;
    char *option, *value;

    if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
        == NULL) return;

    /* Process option - value pairs. */
    for (j = 3; j < c->argc; j += 2) {
        option = c->argv[j]->ptr;
        value = c->argv[j+1]->ptr;
        robj *o = c->argv[j+1];
        long long ll;

        if (!strcasecmp(option,"down-after-milliseconds")) {
            /* down-after-millisecodns <milliseconds> */
            if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0)
                goto badfmt;
            ri->down_after_period = ll;
            changes++;
        } else if (!strcasecmp(option,"failover-timeout")) {
            /* failover-timeout <milliseconds> */
            if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0)
                goto badfmt;
            ri->failover_timeout = ll;
            changes++;
       } else if (!strcasecmp(option,"parallel-syncs")) {
            /* parallel-syncs <milliseconds> */
            if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0)
                goto badfmt;
            ri->parallel_syncs = ll;
            changes++;
       } else if (!strcasecmp(option,"notification-script")) {
            /* notification-script <path> */
            if (strlen(value) && access(value,X_OK) == -1) {
                addReplyError(c,
                    "Notification script seems non existing or non executable");
                return;
            }
            sdsfree(ri->notification_script);
            ri->notification_script = strlen(value) ? sdsnew(value) : NULL;
            changes++;
       } else if (!strcasecmp(option,"client-reconfig-script")) {
            /* client-reconfig-script <path> */
            if (strlen(value) && access(value,X_OK) == -1) {
                addReplyError(c,
                    "Client reconfiguration script seems non existing or "
                    "non executable");
                return;
            }
            sdsfree(ri->client_reconfig_script);
            ri->client_reconfig_script = strlen(value) ? sdsnew(value) : NULL;
            changes++;
       } else if (!strcasecmp(option,"auth-pass")) {
            /* auth-pass <password> */
            sdsfree(ri->auth_pass);
            ri->auth_pass = strlen(value) ? sdsnew(value) : NULL;
            changes++;
        }
    }

    if (changes) sentinelFlushConfig();
    addReply(c,shared.ok);
    return;

badfmt: /* Bad format errors */
    if (changes) sentinelFlushConfig();
    addReplyErrorFormat(c,"Invalid argument '%s' for SENTINEL SET '%s'",
            value, option);
}