        }

        /* Can't replicate a slave. */
        if (n->slaveof != NULL) {
            addReplyError(c,"I can only replicate a master, not a slave.");
            return;
        }
