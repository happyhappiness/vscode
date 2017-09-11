            server.cluster->stats_bus_messages_sent,
            server.cluster->stats_bus_messages_received
        );
        addReplyBulkSds(c, info);
    } else if (!strcasecmp(c->argv[1]->ptr,"saveconfig") && c->argc == 2) {
        int retval = clusterSaveConfig(1);

