static void lremCommand(redisClient *c) {
    dictEntry *de;
    
    de = dictFind(c->dict,c->argv[1]);
    if (de == NULL) {
        addReply(c,shared.minus1);
    } else {
        robj *o = dictGetEntryVal(de);
        
        if (o->type != REDIS_LIST) {
            addReply(c,shared.wrongtypeerr);
        } else {
            list *list = o->ptr;
            listNode *ln, *next;
            int toremove = atoi(c->argv[2]->ptr);
            int removed = 0;
            int fromtail = 0;

            if (toremove < 0) {
                toremove = -toremove;
                fromtail = 1;
            }
            ln = fromtail ? list->tail : list->head;
            while (ln) {
                next = fromtail ? ln->prev : ln->next;
                robj *ele = listNodeValue(ln);
                if (sdscmp(ele->ptr,c->argv[3]->ptr) == 0) {
                    listDelNode(list,ln);
                    server.dirty++;
                    removed++;
                    if (toremove && removed == toremove) break;
                }
                ln = next;
            }
            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
        }
    }
}