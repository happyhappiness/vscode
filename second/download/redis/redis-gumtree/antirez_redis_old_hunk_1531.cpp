            addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
            return;
        }
    } config_set_special_field("loglevel") {
        if (!strcasecmp(o->ptr,"warning")) {
            server.verbosity = REDIS_WARNING;
        } else if (!strcasecmp(o->ptr,"notice")) {
            server.verbosity = REDIS_NOTICE;
        } else if (!strcasecmp(o->ptr,"verbose")) {
            server.verbosity = REDIS_VERBOSE;
        } else if (!strcasecmp(o->ptr,"debug")) {
            server.verbosity = REDIS_DEBUG;
        } else {
            goto badfmt;
        }
    } config_set_special_field("client-output-buffer-limit") {
        int vlen, j;
        sds *v = sdssplitlen(o->ptr,sdslen(o->ptr)," ",1,&vlen);
