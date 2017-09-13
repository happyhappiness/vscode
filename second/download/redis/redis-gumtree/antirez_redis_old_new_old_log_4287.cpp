addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n%s\r\n",
        strlen(buf),buf));