        } else {
            robj *ele = dictGetEntryKey(de);

            addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",sdslen(ele->ptr)));
            addReply(c,ele);
            addReply(c,shared.crlf);
            dictDelete(set->ptr,ele);
