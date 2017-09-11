    }
}

/* Use CLIENT SETNAME to name the connection in the Redis instance as
 * sentinel-<first_8_chars_of_runid>-<connection_type>
 * The connection type is "cmd" or "pubsub" as specified by 'type'.
 *
 * This makes it possible to list all the sentinel instances connected
 * to a Redis servewr with CLIENT LIST, grepping for a specific name format. */
void sentinelSetClientName(sentinelRedisInstance *ri, redisAsyncContext *c, char *type) {
    char name[64];

    snprintf(name,sizeof(name),"sentinel-%.8s-%s",server.runid,type);
    if (redisAsyncCommand(c, sentinelDiscardReplyCallback, NULL,
        "CLIENT SETNAME %s", name) == REDIS_OK)
    {
        ri->pending_commands++;
    }
}

/* Create the async connections for the specified instance if the instance
 * is disconnected. Note that the SRI_DISCONNECTED flag is set even if just
 * one of the two links (commands and pub/sub) is missing. */
