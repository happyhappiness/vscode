        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll <= 0) goto badfmt;
        server.cluster_node_timeout = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-migration-barrier")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll < 0) goto badfmt;
        server.cluster_migration_barrier = ll;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
