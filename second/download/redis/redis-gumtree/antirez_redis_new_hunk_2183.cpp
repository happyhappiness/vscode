        }

        /* I can't replicate myself. */
        if (n == myself) {
            addReplyError(c,"Can't replicate myself");
            return;
        }
