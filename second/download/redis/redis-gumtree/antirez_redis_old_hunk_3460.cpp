}

static void randomizeClientKey(client c) {
    char *p, *newline;
    char buf[32];
    long r;

    if (c->randptr == NULL) return;

    /* Check if we have to randomize (only once per connection) */
    if (c->randptr == (void*)-1) {
        p = strstr(c->obuf,":rand:");
        if (!p) {
            c->randptr = NULL;
            return;
        } else {
            newline = strstr(p,"\r\n");
            assert(newline-(p+6) == 12); /* 12 chars for randomness */
            c->randptr = p+6;
        }
    }

    /* Set random number in output buffer */
    r = random() % config.randomkeys_keyspacelen;
    snprintf(buf,sizeof(buf),"%012ld",r);
    memcpy(c->randptr,buf,12);
}

static void clientDone(client c) {
