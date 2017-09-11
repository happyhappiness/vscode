         * This fd was recently returned from aeApiPoll.  It should be safe to
         * assume that the consumer has processed that poll event, but we play
         * it safer by simply updating pending_mask.  The fd will be
         * re-associated as usual when aeApiPoll is called again.
         */
        if (evport_debug)
            fprintf(stderr, "aeApiAddEvent: adding to pending fd %d\n", fd);
