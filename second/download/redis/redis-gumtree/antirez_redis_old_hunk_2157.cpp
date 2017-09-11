             * itself also clears the importing status. */
            if (n == myself &&
                server.cluster->importing_slots_from[slot])
                server.cluster->importing_slots_from[slot] = NULL;
            clusterDelSlot(slot);
            clusterAddSlot(n,slot);
        } else {
            addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
            return;
        }
        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {
        /* CLUSTER INFO */
