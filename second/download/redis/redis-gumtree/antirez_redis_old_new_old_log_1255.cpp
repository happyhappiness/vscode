addReplyErrorFormat(c,"Target instance replied with error: %s",
                (cs->last_dbid != dbid && buf1[0] == '-') ? buf1+1 : buf2+1);