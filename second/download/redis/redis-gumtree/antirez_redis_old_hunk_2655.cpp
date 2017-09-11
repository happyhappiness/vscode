            fprintf(stderr,"%s: %s\n",config.hostsocket,c->context->errstr);
        exit(1);
    }
    /* Queue N requests accordingly to the pipeline size. */
    c->obuf = sdsempty();
    for (j = 0; j < config.pipeline; j++)
