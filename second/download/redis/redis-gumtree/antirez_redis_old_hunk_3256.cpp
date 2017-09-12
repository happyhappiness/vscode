
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
