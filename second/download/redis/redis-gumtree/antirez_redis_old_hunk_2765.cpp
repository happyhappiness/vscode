        addReplyError(c,"DISCARD without MULTI");
        return;
    }

    freeClientMultiState(c);
    initClientMultiState(c);
    c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS);;
    unwatchAllKeys(c);
    addReply(c,shared.ok);
}

