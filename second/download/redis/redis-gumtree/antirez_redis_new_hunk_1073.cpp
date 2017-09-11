    long long tval;

    if (getLongLongFromObjectOrReply(c,object,&tval,
        "timeout is not an integer or out of range") != C_OK)
        return C_ERR;

    if (tval < 0) {
        addReplyError(c,"timeout is negative");
        return C_ERR;
    }

    if (tval > 0) {
