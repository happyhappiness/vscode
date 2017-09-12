            fprintf(stderr,"%s: %s\n",config.hostsocket,c->context->errstr);
        exit(1);
    }
    c->obuf = sdsnewlen(cmd,len);
    c->randlen = 0;
    c->written = 0;
