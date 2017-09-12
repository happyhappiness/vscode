                    if (withscores)
                        addReplyDouble(c,ln->score);
                }
                ln = ln->level[0].forward;
                rangelen++;
                if (limit > 0) limit--;
            }
            if (justcount) {
                addReplyLongLong(c,(long)rangelen);
            } else {
                setDeferredMultiBulkLength(c,replylen,
                     withscores ? (rangelen*2) : rangelen);
            }
        }
