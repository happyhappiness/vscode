        fprintf(stderr,"Error: %s\n",c->context->errstr);
        exit(1);
    } else {
        if (redisGetReply(c->context,&reply) != REDIS_OK) {
            fprintf(stderr,"Error: %s\n",c->context->errstr);
            exit(1);
        }
        if (reply != NULL) {
            if (reply == (void*)REDIS_REPLY_ERROR) {
                fprintf(stderr,"Unexpected error reply, exiting...\n");
                exit(1);
            }

            if (config.requests_finished < config.requests)
                config.latency[config.requests_finished++] = c->latency;
            clientDone(c);
        }
    }
}
