        for (i = 2; i < c->argc; i++) {
            addReplyCommand(c, dictFetchValue(server.commands, c->argv[i]->ptr));
        }
    } else {
        addReplyError(c, "Unknown subcommand.");
        return;
    }
}
