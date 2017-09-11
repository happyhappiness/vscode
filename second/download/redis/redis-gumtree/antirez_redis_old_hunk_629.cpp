            server.lua_kill = 1;
            addReply(c,shared.ok);
        }
    } else {
        addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
    }
