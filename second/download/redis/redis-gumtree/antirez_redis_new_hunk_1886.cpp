    return REDIS_OK;
}

static void cliPrintContextError(void) {
    if (context == NULL) return;
    fprintf(stderr,"Error: %s\n",context->errstr);
}
