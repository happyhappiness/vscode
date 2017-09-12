        } else {
            robj *ele = dictGetEntryKey(de);

            addReplyBulkLen(c,ele);
            addReply(c,ele);
            addReply(c,shared.crlf);
            dictDelete(set->ptr,ele);
