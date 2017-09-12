                if (limit > 0) limit--;
            }
            if (justcount) {
                addReplyLong(c,(long)rangelen);
            } else {
                lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",
                     withscores ? (rangelen*2) : rangelen);
