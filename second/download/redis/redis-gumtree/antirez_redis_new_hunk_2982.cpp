                    dictEntry *de;

                    while((de = dictNext(di)) != NULL) {
                        robj *eleobj = dictGetKey(de);
                        double *score = dictGetVal(de);

                        snprintf(buf,sizeof(buf),"%.17g",*score);
                        memset(eledigest,0,20);
