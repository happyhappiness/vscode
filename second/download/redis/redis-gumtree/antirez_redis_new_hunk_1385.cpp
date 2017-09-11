
    /* Log the message if the log level allows it to be logged. */
    if (level >= server.verbosity)
        serverLog(level,"%s %s",type,msg);

    /* Publish the message via Pub/Sub if it's not a debugging one. */
    if (level != REDIS_DEBUG) {
