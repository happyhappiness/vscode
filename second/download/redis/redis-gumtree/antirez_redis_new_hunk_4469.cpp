            robj *ele;

            ele = dictGetEntryKey(de);
            addReplyBulkLen(c,ele);
            addReply(c,ele);
            addReply(c,shared.crlf);
        }
