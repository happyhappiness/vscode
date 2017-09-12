serverLog(REDIS_VERBOSE,"Write error sending RDB preamble to slave: %s",
                strerror(errno));