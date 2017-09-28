                    addReplyLongLong(c, start); /* low */
                    addReplyLongLong(c, j-1);   /* high */
                }
                start = -1;

                /* First node reply position is always the master */
                addReplyMultiBulkLen(c, 2);
                addReplyBulkCString(c, node->ip);
                addReplyLongLong(c, node->port);

                /* Remaining nodes in reply are replicas for slot range */
                for (i = 0; i < node->numslaves; i++) {
                    /* This loop is copy/pasted from clusterGenNodeDescription()
                     * with modifications for per-slot node aggregation */
                    if (nodeFailed(node->slaves[i])) continue;
                    addReplyMultiBulkLen(c, 2);
                    addReplyBulkCString(c, node->slaves[i]->ip);
                    addReplyLongLong(c, node->slaves[i]->port);
                    nested_elements++;
                }
                setDeferredMultiBulkLength(c, nested_replylen, nested_elements);
                num_masters++;
            }
        }
    }
    dictReleaseIterator(di);
    setDeferredMultiBulkLength(c, slot_replylen, num_masters);
}

void clusterCommand(redisClient *c) {
    if (server.cluster_enabled == 0) {
        addReplyError(c,"This instance has cluster support disabled");
        return;
    }

    if (!strcasecmp(c->argv[1]->ptr,"meet") && c->argc == 4) {
        long long port;

        if (getLongLongFromObject(c->argv[3], &port) != REDIS_OK) {
            addReplyErrorFormat(c,"Invalid TCP port specified: %s",
                                (char*)c->argv[3]->ptr);
            return;
        }

        if (clusterStartHandshake(c->argv[2]->ptr,port) == 0 &&
