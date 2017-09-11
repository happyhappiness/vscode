        decrRefCount(value);

        /* Delete the source list when it is empty */
        if (listTypeLength(sobj) == 0) dbDelete(c->db,touchedkey);
        signalModifiedKey(c->db,touchedkey);
        decrRefCount(touchedkey);
        server.dirty++;
