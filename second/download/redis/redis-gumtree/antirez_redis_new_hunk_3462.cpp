            fprintf(stderr,"%s: %s\n",config.hostsocket,c->context->errstr);
        exit(1);
    }
    c->state = CLIENT_CONNECTING;
    c->obuf = NULL;
    c->randptr = (void*)-1;
