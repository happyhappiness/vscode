
    printf("Stress with random payloads of different encoding:\n");
    {
        int i,j,len,where;
        unsigned char *p;
        char buf[1024];
        list *ref;
        listNode *refnode;

        /* Hold temp vars from ziplist */
        unsigned char *sstr;
        unsigned int slen;
        long long sval;

        /* In the regression for the cascade bug, it was triggered
         * with a random seed of 2. */
        srand(2);

        for (i = 0; i < 20000; i++) {
            zl = ziplistNew();
            ref = listCreate();
            listSetFreeMethod(ref,sdsfree);
            len = rand() % 256;

            /* Create lists */
            for (j = 0; j < len; j++) {
                where = (rand() & 1) ? ZIPLIST_HEAD : ZIPLIST_TAIL;
                switch(rand() % 4) {
                case 0:
                    sprintf(buf,"%lld",(0LL + rand()) >> 20);
                    break;
                case 1:
                    sprintf(buf,"%lld",(0LL + rand()));
                    break;
                case 2:
                    sprintf(buf,"%lld",(0LL + rand()) << 20);
                    break;
                case 3:
                    randstring(buf,0,256);
                break;
                default:
                    assert(NULL);
                }

                /* Add to ziplist */
                zl = ziplistPush(zl, (unsigned char*)buf, strlen(buf), where);

                /* Add to reference list */
                if (where == ZIPLIST_HEAD) {
                    listAddNodeHead(ref,sdsnew(buf));
                } else if (where == ZIPLIST_TAIL) {
                    listAddNodeTail(ref,sdsnew(buf));
                } else {
                    assert(NULL);
                }
            }

            assert(listLength(ref) == ziplistLen(zl));
            for (j = 0; j < len; j++) {
                /* Naive way to get elements, but similar to the stresser
                 * executed from the Tcl test suite. */
                p = ziplistIndex(zl,j);
                refnode = listIndex(ref,j);

                assert(ziplistGet(p,&sstr,&slen,&sval));
                if (sstr == NULL) {
                    sprintf(buf,"%lld",sval);
                } else {
                    memcpy(buf,sstr,slen);
                    buf[slen] = '\0';
                }
                assert(strcmp(buf,listNodeValue(refnode)) == 0);
            }
            zfree(zl);
            listRelease(ref);
        }
        printf("SUCCESS\n\n");
    }
