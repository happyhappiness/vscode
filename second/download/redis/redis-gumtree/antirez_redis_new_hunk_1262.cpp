        break;
    }
    lastlog_time = time(NULL);
    serverLog(REDIS_WARNING,"Currently unable to failover: %s", msg);
}

/* This function implements the final part of automatic and manual failovers,
