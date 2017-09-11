        server.active_expire_enabled = atoi(c->argv[2]->ptr);
        addReply(c,shared.ok);
    } else {
        addReplyErrorFormat(c, "Unknown DEBUG subcommand '%s'",
            (char*)c->argv[1]->ptr);
    }
}
