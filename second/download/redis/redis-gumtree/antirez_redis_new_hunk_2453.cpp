            /* CLUSTER SETSLOT <SLOT> NODE <NODE ID> */
            clusterNode *n = clusterLookupNode(c->argv[4]->ptr);

            if (!n) {
                addReplyErrorFormat(c,"Unknown node %s",
                    (char*)c->argv[4]->ptr);
                return;
            }
            /* If this hash slot was served by 'myself' before to switch
             * make sure there are no longer local keys for this hash slot. */
            if (server.cluster->slots[slot] == server.cluster->myself &&
