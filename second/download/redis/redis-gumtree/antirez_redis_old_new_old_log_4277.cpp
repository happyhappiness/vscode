addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n%s\r\n",
        strlen(buf),buf));