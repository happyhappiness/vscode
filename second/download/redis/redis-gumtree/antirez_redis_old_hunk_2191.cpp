            return;
        }

        /* We should have no assigned slots to accept to replicate some
         * other node. */
        if (server.cluster->myself->numslots != 0 ||
            dictSize(server.db[0].dict) != 0)
        {
            addReplyError(c,"To set a master the node must be empty and without assigned slots.");
            return;
