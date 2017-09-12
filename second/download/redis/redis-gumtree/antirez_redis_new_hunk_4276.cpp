                addReplyBulkLen(c,ele);
                addReply(c,ele);
                addReply(c,shared.crlf);
                if (withscores)
                    addReplyDouble(c,ln->score);
                ln = ln->forward[0];
                rangelen++;
                if (limit > 0) limit--;
            }
            lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",
		 withscores ? (rangelen*2) : rangelen);
        }
    }
}
