            }
            server.cluster.importing_slots_from[slot] = n;
        } else if (!strcasecmp(c->argv[3]->ptr,"stable") && c->argc == 4) {
            /* CLUSTER SETSLOT <SLOT> STABLE */
            server.cluster.importing_slots_from[slot] = NULL;
            server.cluster.migrating_slots_to[slot] = NULL;
        } else if (!strcasecmp(c->argv[3]->ptr,"node") && c->argc == 4) {
            /* CLUSTER SETSLOT <SLOT> NODE <NODE ID> */
            clusterNode *n = clusterLookupNode(c->argv[4]->ptr);

            if (!n) addReplyErrorFormat(c,"Unknown node %s",
                (char*)c->argv[4]->ptr);
            /* If this hash slot was served by 'myself' before to switch
             * make sure there are no longer local keys for this hash slot. */
            if (server.cluster.slots[slot] == server.cluster.myself &&
                n != server.cluster.myself)
            {
                int numkeys;
                robj **keys;

                keys = zmalloc(sizeof(robj*)*1);
                numkeys = GetKeysInSlot(slot, keys, 1);
                zfree(keys);
                if (numkeys == 0) {
                    addReplyErrorFormat(c, "Can't assign hashslot %d to a different node while I still hold keys for this hash slot.", slot);
                    return;
                }
            }
            clusterDelSlot(slot);
            clusterAddSlot(n,slot);
        } else {
            addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
            return;
