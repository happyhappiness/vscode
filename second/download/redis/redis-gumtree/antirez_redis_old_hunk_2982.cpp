                    dictEntry *de;

                    while((de = dictNext(di)) != NULL) {
                        robj *eleobj = dictGetEntryKey(de);
                        double *score = dictGetEntryVal(de);

                        snprintf(buf,sizeof(buf),"%.17g",*score);
                        memset(eledigest,0,20);
