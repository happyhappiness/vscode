
    /* Make sure the timeout is not negative */
    if (lltimeout < 0) {
        addReplySds(c,sdsnew("-ERR timeout is negative\r\n"));
        return;
    }

