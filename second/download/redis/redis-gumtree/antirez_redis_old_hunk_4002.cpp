    }

    /* Remove list elements to perform the trim */
    for (j = 0; j < ltrim; j++) {
        ln = listFirst(list);
        listDelNode(list,ln);
    }
    for (j = 0; j < rtrim; j++) {
        ln = listLast(list);
        listDelNode(list,ln);
    }
    if (listLength(list) == 0) dbDelete(c->db,c->argv[1]);
    server.dirty++;
    addReply(c,shared.ok);
}

static void lremCommand(redisClient *c) {
    robj *o;
    list *list;
    listNode *ln, *next;
    int toremove = atoi(c->argv[2]->ptr);
    int removed = 0;
    int fromtail = 0;

    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_LIST)) return;
    list = o->ptr;

    if (toremove < 0) {
        toremove = -toremove;
        fromtail = 1;
    }
    ln = fromtail ? list->tail : list->head;
    while (ln) {
        robj *ele = listNodeValue(ln);

        next = fromtail ? ln->prev : ln->next;
        if (equalStringObjects(ele,c->argv[3])) {
            listDelNode(list,ln);
            server.dirty++;
            removed++;
            if (toremove && removed == toremove) break;
        }
        ln = next;
    }
    if (listLength(list) == 0) dbDelete(c->db,c->argv[1]);
    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
}

