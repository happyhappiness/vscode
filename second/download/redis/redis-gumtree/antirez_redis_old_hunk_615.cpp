            server.lua_kill = 1;
            addReply(c,shared.ok);
        }
    } else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"debug")) {
        ldbEnable(c);
        addReply(c,shared.ok);
    } else {
        addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
    }
}


