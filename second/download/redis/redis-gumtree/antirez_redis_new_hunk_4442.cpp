            rangelen = (end-start)+1;

            /* Return the result in form of a multi-bulk reply */
            if (reverse) {
                ln = zsl->tail;
                while (start--)
                    ln = ln->backward;
            } else {
                ln = zsl->header->forward[0];
                while (start--)
                    ln = ln->forward[0];
            }

            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
            for (j = 0; j < rangelen; j++) {
                ele = ln->obj;
                addReplyBulkLen(c,ele);
                addReply(c,ele);
                addReply(c,shared.crlf);
                ln = reverse ? ln->backward : ln->forward[0];
            }
        }
    }
}

static void zrangeCommand(redisClient *c) {
    zrangeGenericCommand(c,0);
}

static void zrevrangeCommand(redisClient *c) {
    zrangeGenericCommand(c,1);
}

static void zlenCommand(redisClient *c) {
    robj *o;
    zset *zs;
