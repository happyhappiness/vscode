        serverLog(REDIS_WARNING,
            "New configEpoch set to %llu",
            (unsigned long long) myself->configEpoch);
        return REDIS_OK;
    } else {
        return REDIS_ERR;
    }
}

