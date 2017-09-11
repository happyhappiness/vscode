        pushed++;
    }
    addReplyLongLong(c, waiting + (lobj ? listTypeLength(lobj) : 0));
    if (pushed) signalModifiedKey(c->db,c->argv[1]);
    server.dirty += pushed;
}

