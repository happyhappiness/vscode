
            /* Return the result in form of a multi-bulk reply */
            if (reverse) {
                ln = zslGetElementByRank(zsl, llen - start);
            } else {
                ln = zslGetElementByRank(zsl, start + 1);
            }

            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",
