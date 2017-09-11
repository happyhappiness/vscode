        }

        /* Can't replicate a slave. */
        if (nodeIsSlave(n)) {
            addReplyError(c,"I can only replicate a master, not a slave.");
            return;
        }
