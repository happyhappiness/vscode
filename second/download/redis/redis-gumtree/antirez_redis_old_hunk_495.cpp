    }
    listTypeReleaseIterator(li);

    if (listTypeLength(subject) == 0) {
        dbDelete(c->db,c->argv[1]);
    }

    addReplyLongLong(c,removed);
    if (removed) signalModifiedKey(c->db,c->argv[1]);
}

/* This is the semantic of this command:
