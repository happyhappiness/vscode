            return;
        }
        clusterDelNodeSlots(server.cluster->myself);
        clusterUpdateState();
        clusterSaveConfigOrDie();
        addReply(c,shared.ok);
    } else if ((!strcasecmp(c->argv[1]->ptr,"addslots") ||
               !strcasecmp(c->argv[1]->ptr,"delslots")) && c->argc >= 3)
