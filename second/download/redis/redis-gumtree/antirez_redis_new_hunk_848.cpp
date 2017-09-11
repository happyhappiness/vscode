        addReplyError(c,"This instance has cluster support disabled");
        return;
    }
    c->flags |= CLIENT_ASKING;
    addReply(c,shared.ok);
}

