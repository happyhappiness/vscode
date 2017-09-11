    }

    /* Check if the TTL value makes sense */
    if (getLongLongFromObjectOrReply(c,c->argv[2],&ttl,NULL) != C_OK) {
        return;
    } else if (ttl < 0) {
        addReplyError(c,"Invalid TTL value, must be >= 0");
        return;
    }

    /* Verify RDB version and data checksum. */
    if (verifyDumpPayload(c->argv[3]->ptr,sdslen(c->argv[3]->ptr)) == C_ERR)
    {
        addReplyError(c,"DUMP payload version or checksum are wrong");
        return;
