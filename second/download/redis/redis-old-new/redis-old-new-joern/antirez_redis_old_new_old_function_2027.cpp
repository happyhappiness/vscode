void rewriteConfigClientoutputbufferlimitOption(struct rewriteConfigState *state) {
    int j;
    char *option = "client-output-buffer-limit";

    for (j = 0; j < REDIS_CLIENT_LIMIT_NUM_CLASSES; j++) {
        int force = (server.client_obuf_limits[j].hard_limit_bytes !=
                    clientBufferLimitsDefaults[j].hard_limit_bytes) ||
                    (server.client_obuf_limits[j].soft_limit_bytes !=
                    clientBufferLimitsDefaults[j].soft_limit_bytes) ||
                    (server.client_obuf_limits[j].soft_limit_seconds !=
                    clientBufferLimitsDefaults[j].soft_limit_seconds);
        sds line;

        line = sdscatprintf(sdsempty(),"%s %s %llu %llu %ld",
                option,
                getClientLimitClassName(j),
                server.client_obuf_limits[j].hard_limit_bytes,
                server.client_obuf_limits[j].soft_limit_bytes,
                (long) server.client_obuf_limits[j].soft_limit_seconds);
        rewriteConfigRewriteLine(state,option,line,force);
    }
}