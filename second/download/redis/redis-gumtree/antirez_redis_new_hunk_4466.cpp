            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
            for (j = 0; j < rangelen; j++) {
                ele = listNodeValue(ln);
                addReplyBulkLen(c,ele);
                addReply(c,ele);
                addReply(c,shared.crlf);
                ln = ln->next;
