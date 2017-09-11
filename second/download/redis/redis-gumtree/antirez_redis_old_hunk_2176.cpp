            return;
        }

        if (n->flags & REDIS_NODE_SLAVE) {
            addReplyError(c,"The specified node is not a master");
            return;
        }
