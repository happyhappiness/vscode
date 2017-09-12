        decrRefCount(obj);

    if (listTypeLength(subject) == 0) dbDelete(c->db,c->argv[1]);
    addReplyLongLong(c,removed);
    if (removed) touchWatchedKey(c->db,c->argv[1]);
}

