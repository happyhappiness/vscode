            server.cluster.importing_slots_from[slot] = NULL;
        } else {
            addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
        }
        clusterSaveConfigOrDie();
        addReply(c,shared.ok);
