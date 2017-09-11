        char buf[128];
        char *arg;

        if (c->argv[j]->type == REDIS_STRING &&
            c->argv[j]->encoding == REDIS_ENCODING_RAW)
        {
            arg = (char*) c->argv[j]->ptr;
        } else {
            snprintf(buf,sizeof(buf),"Object type: %d, encoding: %d",
