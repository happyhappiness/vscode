        /* CLUSTER FORGET <NODE ID> */
        clusterNode *n = clusterLookupNode(c->argv[2]->ptr);

        if (n == server.cluster->myself) {
            addReplyErrorFormat(c,"I tried hard but I can't forget myself...");
            return;
        } else if (!n) {
            addReplyErrorFormat(c,"Unknown node %s", (char*)c->argv[2]->ptr);
            return;
        }
        clusterBlacklistAddNode(n);
        clusterDelNode(n);
