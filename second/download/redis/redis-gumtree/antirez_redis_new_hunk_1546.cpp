            /* On error assume that last_dbid is no longer valid. */
            cs->last_dbid = -1;
            addReplyErrorFormat(c,"Target instance replied with error: %s",
                (select && buf1[0] == '-') ? buf1+1 : buf2+1);
        } else {
            /* Update the last_dbid in migrateCachedSocket */
            cs->last_dbid = dbid;
