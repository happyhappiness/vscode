    return REDIS_OK;
}

/* Send the INFO command, reconnecting the link if needed. */
static redisReply *reconnectingInfo(void) {
    redisContext *c = context;
    redisReply *reply = NULL;
    int tries = 0;

    assert(!c->err);
    while(reply == NULL) {
        while (c->err & (REDIS_ERR_IO | REDIS_ERR_EOF)) {
            printf("Reconnecting (%d)...\r", ++tries);
            fflush(stdout);

            redisFree(c);
            c = redisConnect(config.hostip,config.hostport);
            usleep(1000000);
        }

        reply = redisCommand(c,"INFO");
        if (c->err && !(c->err & (REDIS_ERR_IO | REDIS_ERR_EOF))) {
            fprintf(stderr, "Error: %s\n", c->errstr);
            exit(1);
        } else if (tries > 0) {
            printf("\n");
        }
    }

    context = c;
    return reply;
}

/*------------------------------------------------------------------------------
 * User interface
 *--------------------------------------------------------------------------- */
