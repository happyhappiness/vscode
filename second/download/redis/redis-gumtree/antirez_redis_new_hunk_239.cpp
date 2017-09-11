    }
}

void debugCommand(client *c) {
    if (c->argc == 1) {
        addReplyError(c,"You must specify a subcommand for DEBUG. Try DEBUG HELP for info.");
