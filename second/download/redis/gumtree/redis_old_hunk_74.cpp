        ri->client_reconfig_script = sdsnew(argv[2]);
   } else if (!strcasecmp(argv[0],"auth-pass") && argc == 3) {
        /* auth-pass <name> <password> */
        ri = sentinelGetMasterByName(argv[1]);
        if (!ri) return "No such master with specified name.";
        ri->auth_pass = sdsnew(argv[2]);
    } else {
        return "Unrecognized sentinel configuration statement.";
    }
    return NULL;
}

/* ====================== hiredis connection handling ======================= */

/* Completely disconnect an hiredis link from an instance. */
void sentinelKillLink(sentinelRedisInstance *ri, redisAsyncContext *c) {
    if (ri->cc == c) {
        ri->cc = NULL;
