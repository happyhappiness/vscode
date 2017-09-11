        sdsfree(o);
    } else if (!strcasecmp(c->argv[1]->ptr,"kill")) {
        /* CLIENT KILL <ip:port>
         * CLIENT KILL <attrib> <value> */
        char *addr = NULL;
        int type = -1;
        uint64_t id = 0;
        int killed = 0;
        int close_this_client = 0;

        /* Parse arguments. */
        if (c->argc == 3) {
            addr = c->argv[2]->ptr;
        } else if (c->argc == 4) {
            if (!strcasecmp(c->argv[2]->ptr,"id")) {
                long long tmp;

                if (getLongLongFromObjectOrReply(c,c->argv[3],&tmp,NULL)
                    != REDIS_OK) return;
                id = tmp;
            } else if (!strcasecmp(c->argv[2]->ptr,"type")) {
                type = getClientTypeByName(c->argv[3]->ptr);
                if (type == -1) {
                    addReplyErrorFormat(c,"Unknown client type '%s'",
                        (char*) c->argv[3]->ptr);
                    return;
                }
            } else if (!strcasecmp(c->argv[2]->ptr,"addr")) {
                addr = c->argv[3]->ptr;
            } else {
                addReply(c,shared.syntaxerr);
                return;
            }
        } else {
            addReply(c,shared.syntaxerr);
