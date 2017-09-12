                    ln = ln->forward[0];
            }

            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",
                withscores ? (rangelen*2) : rangelen));
            for (j = 0; j < rangelen; j++) {
                ele = ln->obj;
                addReplyBulkLen(c,ele);
                addReply(c,ele);
                addReply(c,shared.crlf);
                if (withscores)
                    addReplyDouble(c,ln->score);
                ln = reverse ? ln->backward : ln->forward[0];
            }
        }
