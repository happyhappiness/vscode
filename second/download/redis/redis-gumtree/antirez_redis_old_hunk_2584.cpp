                    znode = zslInsert(zs->zsl,score,curobj);
                    incrRefCount(curobj); /* Re-inserted in skiplist. */
                    dictGetVal(de) = &znode->score; /* Update score ptr. */

                    signalModifiedKey(c->db,key);
                    server.dirty++;
                }
            } else {
                znode = zslInsert(zs->zsl,score,ele);
                incrRefCount(ele); /* Inserted in skiplist. */
                redisAssertWithInfo(c,NULL,dictAdd(zs->dict,ele,&znode->score) == DICT_OK);
                incrRefCount(ele); /* Added to dictionary. */

                signalModifiedKey(c->db,key);
                server.dirty++;
                if (!incr) added++;
            }
        } else {
            redisPanic("Unknown sorted set encoding");
        }
    }
    zfree(scores);
    if (incr) /* ZINCRBY */
        addReplyDouble(c,score);
    else /* ZADD */
        addReplyLongLong(c,added);
}

void zaddCommand(redisClient *c) {
