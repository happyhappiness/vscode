  redisSrand48(luaL_checkint(L, 1));
  return 0;
}

/* ---------------------------------------------------------------------------
 * SCRIPT command for script environment introspection and control
 * ------------------------------------------------------------------------- */

void scriptCommand(redisClient *c) {
    if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"flush")) {
        scriptingReset();
        addReply(c,shared.ok);
        server.dirty++; /* Replicating this command is a good idea. */
    } else if (c->argc >= 2 && !strcasecmp(c->argv[1]->ptr,"exists")) {
        int j;

        addReplyMultiBulkLen(c, c->argc-2);
        for (j = 2; j < c->argc; j++) {
            if (dictFind(server.lua_scripts,c->argv[j]->ptr))
                addReply(c,shared.cone);
            else
                addReply(c,shared.czero);
        }
    } else {
        addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
    }
}
