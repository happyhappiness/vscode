            decrRefCount(lenobj);

            while(ln && ln->score <= max) {
                if (offset) {
                    offset--;
                    ln = ln->forward[0];
                    continue;
                }
                if (limit == 0) break;
                ele = ln->obj;
                addReplyBulkLen(c,ele);
                addReply(c,ele);
                addReply(c,shared.crlf);
                ln = ln->forward[0];
                rangelen++;
                if (limit > 0) limit--;
            }
            lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",rangelen);
        }
