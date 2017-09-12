            decrRefCount(lenobj);

            while(ln && ln->score <= max) {
                ele = ln->obj;
                addReplyBulkLen(c,ele);
                addReply(c,ele);
                addReply(c,shared.crlf);
                ln = ln->forward[0];
                rangelen++;
            }
            lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",rangelen);
        }
