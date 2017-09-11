    if (newline == NULL) {
        if (sdslen(c->querybuf) > PROTO_INLINE_MAX_SIZE) {
            addReplyError(c,"Protocol error: too big inline request");
            setProtocolError("too big inline request",c,0);
        }
        return C_ERR;
    }
