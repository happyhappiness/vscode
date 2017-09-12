            if (end >= llen) end = llen-1;
            rangelen = (end-start)+1;

            /* Return the result in form of a multi-bulk reply */
            if (reverse) {
                ln = zslGetElementByRank(zsl, llen - start);
            } else {
                ln = zslGetElementByRank(zsl, start + 1);
            }

            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",
                withscores ? (rangelen*2) : rangelen));
            for (j = 0; j < rangelen; j++) {
