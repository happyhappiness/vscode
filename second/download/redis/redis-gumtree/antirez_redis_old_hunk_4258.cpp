            if (end >= llen) end = llen-1;
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

            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",
                withscores ? (rangelen*2) : rangelen));
            for (j = 0; j < rangelen; j++) {
