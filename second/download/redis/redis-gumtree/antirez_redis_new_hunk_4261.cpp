            if (end >= llen) end = llen-1;
            rangelen = (end-start)+1;

            /* check if starting point is trivial, before searching
             * the element in log(N) time */
            if (reverse) {
                ln = start == 0 ? zsl->tail : zslGetElementByRank(zsl, llen - start);
            } else {
                ln = start == 0 ? zsl->header->forward[0] : zslGetElementByRank(zsl, start + 1);
            }

            /* Return the result in form of a multi-bulk reply */
            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",
                withscores ? (rangelen*2) : rangelen));
            for (j = 0; j < rangelen; j++) {
