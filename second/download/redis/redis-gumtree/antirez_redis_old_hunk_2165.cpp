            addReplyBulkCString(c,ni);
            sdsfree(ni);
        }
    } else {
        addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
    }
