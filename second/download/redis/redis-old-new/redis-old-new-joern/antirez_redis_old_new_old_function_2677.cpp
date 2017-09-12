static int cliReadReply(int output_raw_strings) {
    void *_reply;
    redisReply *reply;
    sds out;

    if (redisGetReply(context,&_reply) != REDIS_OK) {
        if (config.shutdown)
            return REDIS_OK;
        if (config.interactive) {
            /* Filter cases where we should reconnect */
            if (context->err == REDIS_ERR_IO && errno == ECONNRESET)
                return REDIS_ERR;
            if (context->err == REDIS_ERR_EOF)
                return REDIS_ERR;
        }
        cliPrintContextError();
        exit(1);
        return REDIS_ERR; /* avoid compiler warning */
    }

    reply = (redisReply*)_reply;
    if (output_raw_strings) {
        out = cliFormatReplyRaw(reply);
    } else {
        if (config.raw_output) {
            out = cliFormatReplyRaw(reply);
            out = sdscat(out,"\n");
        } else {
            out = cliFormatReplyTTY(reply,"");
        }
    }
    fwrite(out,sdslen(out),1,stdout);
    sdsfree(out);
    freeReplyObject(reply);
    return REDIS_OK;
}