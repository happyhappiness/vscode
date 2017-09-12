            if (justcount) {
                addReplyLongLong(c,(long)rangelen);
            } else {
                setDeferredMultiBulkLength(c,replylen,
                     withscores ? (rangelen*2) : rangelen);
            }
        }
