         sdsfree(sha);
         forceCommandPropagation(c,REDIS_PROPAGATE_REPL|REDIS_PROPAGATE_AOF);
     } else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"kill")) {
         if (server.lua_caller == NULL) {
             addReplySds(c,sdsnew("-NOTBUSY No scripts in execution right now.\r\n"));
         } else if (server.lua_write_dirty) {
-            addReplySds(c,sdsnew("-UNKILLABLE Sorry the script already executed write commands against the dataset. You can either wait the script termination or kill the server in an hard way using the SHUTDOWN NOSAVE command.\r\n"));
+            addReplySds(c,sdsnew("-UNKILLABLE Sorry the script already executed write commands against the dataset. You can either wait the script termination or kill the server in a hard way using the SHUTDOWN NOSAVE command.\r\n"));
         } else {
             server.lua_kill = 1;
             addReply(c,shared.ok);
         }
     } else {
         addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
