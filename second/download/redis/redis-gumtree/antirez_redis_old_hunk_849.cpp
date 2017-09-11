        addReplyError(c,"This instance has cluster support disabled");
        return;
    }
    c->flags |= REDIS_READONLY;
    addReply(c,shared.ok);
}

/* The READWRITE command just clears the READONLY command state. */
void readwriteCommand(client *c) {
    c->flags &= ~REDIS_READONLY;
    addReply(c,shared.ok);
}

