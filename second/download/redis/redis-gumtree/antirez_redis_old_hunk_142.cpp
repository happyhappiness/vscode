    long numreplicas, ackreplicas;
    long long offset = c->woff;

    /* Argument parsing. */
    if (getLongFromObjectOrReply(c,c->argv[1],&numreplicas,NULL) != C_OK)
        return;
