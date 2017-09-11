            node->flags &= ~CLUSTER_NODE_MEET;

            serverLog(LL_DEBUG,"Connecting with Node %.40s at %s:%d",
                    node->name, node->ip, node->cport);
        }
    }
    dictReleaseIterator(di);
