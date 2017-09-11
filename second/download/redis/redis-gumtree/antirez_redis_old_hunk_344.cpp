        if (moduleUnload(c->argv[2]->ptr) == C_OK)
            addReply(c,shared.ok);
        else {
            char *errmsg = "operation not possible.";
            switch(errno) {
            case ENOENT: errmsg = "no such module with that name";
            }
            addReplyErrorFormat(c,"Error unloading module: %s",errmsg);
        }
