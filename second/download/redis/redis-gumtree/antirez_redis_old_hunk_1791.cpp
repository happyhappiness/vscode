
        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) {
            uint64_t j;

            for (j = 0; j < ok_slaves[0]; j++) {
                if (slave->id == ok_slaves[j+1]) break; /* Found in OK list. */
            }
            if (j == ok_slaves[0]) {
                redisLog(REDIS_WARNING,
                "Closing slave %llu: child->slave RDB transfer failed.",
                slave->id);
                freeClient(slave);
            } else {
                redisLog(REDIS_WARNING,
