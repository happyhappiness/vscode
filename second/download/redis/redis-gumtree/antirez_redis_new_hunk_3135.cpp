    return REDIS_OK;
}

static void cliPrintContextError() {
    if (context == NULL) return;
    fprintf(stderr,"Error: %s\n",context->errstr);
}

static sds cliFormatReplyTTY(redisReply *r, char *prefix) {
