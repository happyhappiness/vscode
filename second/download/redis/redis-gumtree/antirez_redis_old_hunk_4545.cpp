                ln = listLast(list);

            if (ln == NULL) {
                addReply(c,shared.nil);
            } else {
                robj *ele = listNodeValue(ln);
                addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",(int)sdslen(ele->ptr)));
                addReply(c,ele);
                addReply(c,shared.crlf);
                listDelNode(list,ln);
