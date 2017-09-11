        /* Don't blank lines about options the rewrite process
         * don't understand. */
        if (dictFind(state->rewritten,option) == NULL) {
            redisLog(REDIS_DEBUG,"Not rewritten option: %s", option);
            continue;
        }

