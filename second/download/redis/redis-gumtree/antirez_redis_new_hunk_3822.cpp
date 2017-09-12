
    /* Make sure the timeout is not negative */
    if (lltimeout < 0) {
        addReplyError(c,"timeout is negative");
        return;
    }

