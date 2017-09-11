    } else if (!strcasecmp(c->argv[1]->ptr,"failover") &&
               (c->argc == 2 || c->argc == 3))
    {
        /* CLUSTER FAILOVER [FORCE|TAKEOVER] */
        int force = 0, takeover = 0;

        if (c->argc == 3) {
            if (!strcasecmp(c->argv[2]->ptr,"force")) {
                force = 1;
            } else if (!strcasecmp(c->argv[2]->ptr,"takeover")) {
                takeover = 1;
                force = 1; /* Takeover also implies force. */
            } else {
                addReply(c,shared.syntaxerr);
                return;
            }
        }

        /* Check preconditions. */
        if (nodeIsMaster(myself)) {
            addReplyError(c,"You should send CLUSTER FAILOVER to a slave");
            return;
