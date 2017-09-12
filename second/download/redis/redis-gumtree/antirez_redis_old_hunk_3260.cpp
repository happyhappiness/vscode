        } else {
            addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
        }
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {
        char *statestr[] = {"ok","fail","needhelp"};
