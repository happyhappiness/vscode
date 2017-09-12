        } else {
            addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
        }
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {
        char *statestr[] = {"ok","fail","needhelp"};
        int slots_assigned = 0, slots_ok = 0, slots_pfail = 0, slots_fail = 0;
