        clusterUpdateState();
        clusterSaveConfigOrDie();
        addReply(c,shared.ok);
    } else {
        addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
    }
