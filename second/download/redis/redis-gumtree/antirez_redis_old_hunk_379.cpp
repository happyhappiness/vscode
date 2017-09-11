
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
