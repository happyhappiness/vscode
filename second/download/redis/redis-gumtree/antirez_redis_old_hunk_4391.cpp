            if (!de) {
                addReply(c,shared.nullbulk);
            } else {
                char buf[128];
                double *score = dictGetEntryVal(de);

                snprintf(buf,sizeof(buf),"%.17g",*score);
                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n%s\r\n",
                    strlen(buf),buf));
            }
        }
    }
