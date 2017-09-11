                if (!zslValueLteMax(ln->score,&range)) break;
            }

            /* Do our magic */
            rangelen++;
            if (!justcount) {
                addReplyBulk(c,ln->obj);
                if (withscores)
                    addReplyDouble(c,ln->score);
            }

            /* Move to next node */
            ln = reverse ? ln->backward : ln->level[0].forward;
        }
    } else {
        redisPanic("Unknown sorted set encoding");
    }

    if (justcount) {
        addReplyLongLong(c,(long)rangelen);
    } else {
        if (withscores) rangelen *= 2;
        setDeferredMultiBulkLength(c,replylen,rangelen);
    }
}

void zrangebyscoreCommand(redisClient *c) {
    genericZrangebyscoreCommand(c,0,0);
}

void zrevrangebyscoreCommand(redisClient *c) {
    genericZrangebyscoreCommand(c,1,0);
}

void zcountCommand(redisClient *c) {
    genericZrangebyscoreCommand(c,0,1);
}

void zcardCommand(redisClient *c) {
