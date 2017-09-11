    pushGenericCommand(c,LIST_TAIL);
}

void pushxGenericCommand(client *c, robj *refval, robj *val, int where) {
    robj *subject;
    listTypeIterator *iter;
    listTypeEntry entry;
    int inserted = 0;

    if ((subject = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,subject,OBJ_LIST)) return;

    if (refval != NULL) {
        /* Seek refval from head to tail */
        iter = listTypeInitIterator(subject,0,LIST_TAIL);
        while (listTypeNext(iter,&entry)) {
            if (listTypeEqual(&entry,refval)) {
                listTypeInsert(&entry,val,where);
                inserted = 1;
                break;
            }
        }
        listTypeReleaseIterator(iter);

        if (inserted) {
            signalModifiedKey(c->db,c->argv[1]);
            notifyKeyspaceEvent(NOTIFY_LIST,"linsert",
                                c->argv[1],c->db->id);
            server.dirty++;
        } else {
            /* Notify client of a failed insert */
            addReply(c,shared.cnegone);
            return;
        }
    } else {
        char *event = (where == LIST_HEAD) ? "lpush" : "rpush";

        listTypePush(subject,val,where);
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(NOTIFY_LIST,event,c->argv[1],c->db->id);
        server.dirty++;
    }

    addReplyLongLong(c,listTypeLength(subject));
}

void lpushxCommand(client *c) {
    c->argv[2] = tryObjectEncoding(c->argv[2]);
    pushxGenericCommand(c,NULL,c->argv[2],LIST_HEAD);
}

void rpushxCommand(client *c) {
    c->argv[2] = tryObjectEncoding(c->argv[2]);
    pushxGenericCommand(c,NULL,c->argv[2],LIST_TAIL);
}

void linsertCommand(client *c) {
    c->argv[4] = tryObjectEncoding(c->argv[4]);
    if (strcasecmp(c->argv[2]->ptr,"after") == 0) {
        pushxGenericCommand(c,c->argv[3],c->argv[4],LIST_TAIL);
    } else if (strcasecmp(c->argv[2]->ptr,"before") == 0) {
        pushxGenericCommand(c,c->argv[3],c->argv[4],LIST_HEAD);
    } else {
        addReply(c,shared.syntaxerr);
    }
}

void llenCommand(client *c) {
