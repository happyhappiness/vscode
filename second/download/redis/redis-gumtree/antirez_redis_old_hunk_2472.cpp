         * instances. */
        if (node->flags & REDIS_NODE_MYSELF) {
            for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
                if (server.cluster.migrating_slots_to[j]) {
                    ci = sdscatprintf(ci," [%d->-%.40s]",j,
                        server.cluster.migrating_slots_to[j]->name);
                } else if (server.cluster.importing_slots_from[j]) {
                    ci = sdscatprintf(ci," [%d-<-%.40s]",j,
                        server.cluster.importing_slots_from[j]->name);
                }
            }
        }
