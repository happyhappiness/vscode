        }

        /* I can't replicate myself. */
        if (n == server.cluster->myself) {
            addReplyError(c,"Can't replicate myself");
            return;
        }
