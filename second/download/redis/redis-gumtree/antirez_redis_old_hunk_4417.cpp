                char buf[128];
                double *score = dictGetEntryVal(de);

                snprintf(buf,sizeof(buf),"%.16g",*score);
                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n%s\r\n",
                    strlen(buf),buf));
            }
