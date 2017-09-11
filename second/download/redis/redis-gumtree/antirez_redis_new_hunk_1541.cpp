            appendServerSaveParams(seconds, changes);
        }
        sdsfreesplitres(v,vlen);
    } config_set_special_field("dir") {
        if (chdir((char*)o->ptr) == -1) {
            addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
            return;
        }
    } config_set_special_field("loglevel") {
        if (!strcasecmp(o->ptr,"warning")) {
            server.verbosity = REDIS_WARNING;
        } else if (!strcasecmp(o->ptr,"notice")) {
