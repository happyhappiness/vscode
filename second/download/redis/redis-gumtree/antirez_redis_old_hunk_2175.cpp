        /* If the instance is currently a master, it should have no assigned
         * slots nor keys to accept to replicate some other node.
         * Slaves can switch to another master without issues. */
        if (myself->flags & REDIS_NODE_MASTER &&
            (myself->numslots != 0 ||
            dictSize(server.db[0].dict) != 0))
        {
            addReplyError(c,"To set a master the node must be empty and without assigned slots.");
            return;
        }
