        addReply(c, shared.noscripterr);
        return;
    }
    evalGenericCommand(c,1);
}

void scriptCommand(client *c) {
