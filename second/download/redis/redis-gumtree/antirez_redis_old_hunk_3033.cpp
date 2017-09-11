        clusterSaveConfigOrDie();
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"setslot") && c->argc >= 4) {
        /* SETSLOT 10 MIGRATING <instance ID> */
        /* SETSLOT 10 IMPORTING <instance ID> */
        /* SETSLOT 10 STABLE */
        int slot;
        clusterNode *n;

