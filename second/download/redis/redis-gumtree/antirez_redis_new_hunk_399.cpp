
/* Redis MODULE command.
 *
 * MODULE LOAD <path> [args...] */
void moduleCommand(client *c) {
    char *subcmd = c->argv[1]->ptr;

    if (!strcasecmp(subcmd,"load") && c->argc >= 3) {
        sds *argv = NULL;
        int argc = 0;
        int i;

        if (c->argc > 3) {
            argc = c->argc - 3;
            argv = zmalloc(sizeof(sds)*argc);
            for (i=0; i<argc; i++) {
                argv[i] = (sds) c->argv[i+3]->ptr;
            }
        }

        if (moduleLoad(c->argv[2]->ptr,(void **)argv,argc) == C_OK)
            addReply(c,shared.ok);
        else
            addReplyError(c,
                "Error loading the extension. Please check the server logs.");
        if (argv)
            zfree(argv);
    } else if (!strcasecmp(subcmd,"unload") && c->argc == 3) {
        if (moduleUnload(c->argv[2]->ptr) == C_OK)
            addReply(c,shared.ok);
