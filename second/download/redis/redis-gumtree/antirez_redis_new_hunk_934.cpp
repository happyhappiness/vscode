        return;
    }

    serverLog(LL_NOTICE,"Slave %s asks for synchronization",
        replicationGetSlaveName(c));

    /* Try a partial resynchronization if this is a PSYNC command.
