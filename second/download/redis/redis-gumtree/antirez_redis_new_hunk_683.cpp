                    dictEntry *de;

                    while((de = dictNext(di)) != NULL) {
                        sds sdsele = dictGetKey(de);
                        double *score = dictGetVal(de);

                        snprintf(buf,sizeof(buf),"%.17g",*score);
                        memset(eledigest,0,20);
                        mixDigest(eledigest,sdsele,sdslen(sdsele));
                        mixDigest(eledigest,buf,strlen(buf));
                        xorDigest(digest,eledigest,20);
                    }
