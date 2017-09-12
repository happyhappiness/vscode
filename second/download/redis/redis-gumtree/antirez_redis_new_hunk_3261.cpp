                start = -1;
            }
        }

        /* Just for MYSELF node we also dump info about slots that
         * we are migrating to other instances or importing from other
         * instances. */
        if (node->flags & REDIS_NODE_MYSELF) {
            for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
                if (server.cluster.migrating_slots_to[j]) {
                    ci = sdscatprintf(ci," [%d->%.40s]",j,
                        server.cluster.migrating_slots_to[j]->name);
                } else if (server.cluster.importing_slots_from[j]) {
                    ci = sdscatprintf(ci," [%d<-%.40s]",j,
                        server.cluster.importing_slots_from[j]->name);
                }
            }
        }
        ci = sdscatlen(ci,"\n",1);
    }
    dictReleaseIterator(di);
