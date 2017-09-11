
        /* Set the master. */
        clusterSetMaster(n);
        addReply(c,shared.ok);
    } else {
        addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
