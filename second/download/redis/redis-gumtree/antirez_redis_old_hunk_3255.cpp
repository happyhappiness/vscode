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
