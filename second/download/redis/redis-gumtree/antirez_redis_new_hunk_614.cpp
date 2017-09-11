        addReply(c, shared.noscripterr);
        return;
    }
    if (!(c->flags & CLIENT_LUA_DEBUG))
        evalGenericCommand(c,1);
    else {
        addReplyError(c,"Please use EVAL instead of EVALSHA for debugging");
        return;
    }
}

void scriptCommand(client *c) {
