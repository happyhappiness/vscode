            appendServerSaveParams(seconds, changes);
        }
        sdsfreesplitres(v,vlen);
    } else if (!strcasecmp(c->argv[2]->ptr,"dir")) {
        if (chdir((char*)o->ptr) == -1) {
            addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
            return;
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"loglevel")) {
        if (!strcasecmp(o->ptr,"warning")) {
            server.verbosity = REDIS_WARNING;
        } else if (!strcasecmp(o->ptr,"notice")) {
