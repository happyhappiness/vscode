                                 CLUSTER_TODO_SAVE_CONFIG);
            addReply(c,shared.ok);
        }
    } else {
        addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
    }
