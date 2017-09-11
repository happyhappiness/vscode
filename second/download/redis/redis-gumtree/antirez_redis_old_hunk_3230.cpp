        /* SETSLOT 10 MIGRATING <instance ID> */
        /* SETSLOT 10 IMPORTING <instance ID> */
        /* SETSLOT 10 STABLE */
        long long aux;
        unsigned int slot;
        clusterNode *n;

        if (getLongLongFromObjectOrReply(c,c->argv[2],&aux,NULL) != REDIS_OK)
            return;
        if (aux < 0 || aux >= REDIS_CLUSTER_SLOTS) {
            addReplyError(c,"Slot out of range");
            return;
        }
        slot = (unsigned int) aux;
        if (!strcasecmp(c->argv[3]->ptr,"migrating") && c->argc == 5) {
            if (server.cluster.slots[slot] != server.cluster.myself) {
                addReplyErrorFormat(c,"I'm not the owner of hash slot %u",slot);
