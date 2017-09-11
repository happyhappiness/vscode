            cb = callbacks->head;
            while(cb) {
                if (cb->privdata == ri) {
                    printf("HERE\n");
                    cb->fn = sentinelDiscardReplyCallback;
                    cb->privdata = NULL; /* Not strictly needed. */
                }
