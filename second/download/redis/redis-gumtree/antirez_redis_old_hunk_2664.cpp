            addReplyBulkCString(c,addr->ip);
            addReplyBulkLongLong(c,addr->port);
        }
    } else {
        addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                               (char*)c->argv[1]->ptr);
