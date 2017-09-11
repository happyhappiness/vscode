        }
    } config_set_memory_field("repl-backlog-size",ll) {
        resizeReplicationBacklog(ll);
    }

    /* Everyhing else is an error... */
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
        return;
    }
    addReply(c,shared.ok);
    return;

