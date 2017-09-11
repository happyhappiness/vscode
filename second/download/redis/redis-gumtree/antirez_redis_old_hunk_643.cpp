            rewriteClientCommandArgument(c,0,
                resetRefCount(createStringObject("EVAL",4)));
            rewriteClientCommandArgument(c,1,script);
            forceCommandPropagation(c,PROPAGATE_REPL|PROPAGATE_AOF);
        }
    }

    /* If we are using single commands replication, emit EXEC if there
     * was at least a write. */
    if (server.lua_replicate_commands) {
        preventCommandPropagation(c);
        if (server.lua_multi_emitted) {
            robj *propargv[1];
            propargv[0] = createStringObject("EXEC",4);
            alsoPropagate(server.execCommand,c->db->id,propargv,1,
                PROPAGATE_AOF|PROPAGATE_REPL);
            decrRefCount(propargv[0]);
        }
    }
}

void evalCommand(client *c) {
