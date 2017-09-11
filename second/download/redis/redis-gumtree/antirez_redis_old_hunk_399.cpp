
/* Redis MODULE command.
 *
 * MODULE LOAD <path> */
void moduleCommand(client *c) {
    char *subcmd = c->argv[1]->ptr;

    if (!strcasecmp(subcmd,"load") && c->argc == 3) {
        if (moduleLoad(c->argv[2]->ptr) == C_OK)
            addReply(c,shared.ok);
        else
            addReplyError(c,
                "Error loading the extension. Please check the server logs.");
    } else if (!strcasecmp(subcmd,"unload") && c->argc == 3) {
        if (moduleUnload(c->argv[2]->ptr) == C_OK)
            addReply(c,shared.ok);
