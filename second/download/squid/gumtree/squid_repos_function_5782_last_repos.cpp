char *
getextrasids(char *ad_groups, uint32_t ExtraSids, uint32_t SidCount)
{
    if (ExtraSids!= 0) {
        uint32_t ngroup;
        uint32_t *pa;
        char *ag;
        int l;

        align(4);
        ngroup = get4byt();
        if ( ngroup != SidCount) {
            debug((char *) "%s| %s: ERROR: Group encoding error => SidCount: %d Array size: %d\n",
                  LogTime(), PROGRAM, SidCount, ngroup);
            return NULL;
        }
        debug((char *) "%s| %s: INFO: Found %d ExtraSIDs\n", LogTime(), PROGRAM, SidCount);

        pa=(uint32_t *)xmalloc(SidCount*sizeof(uint32_t));
        for ( l=0; l < (int)SidCount; l++ ) {
            pa[l] = get4byt();
            bpos = bpos+4; /* attr */
        }

        for ( l=0; l<(int)SidCount; l++ ) {
            char es[256];

            if (pa[l] != 0) {
                uint8_t rev;
                uint64_t idauth;

                uint32_t nauth = get4byt();

                // check if nauth math will produce invalid length values on 32-bit
                static uint32_t maxGidCount = (UINT32_MAX-1-1-6)/4;
                if (nauth > maxGidCount) {
                    debug((char *) "%s| %s: ERROR: Too many extra groups ! count > %d : %s\n",
                          LogTime(), PROGRAM, maxGidCount, ad_groups);
                    xfree(pa);
                    return NULL;
                }

                size_t length = 1+1+6+nauth*4;
                ag = (char *)xcalloc((length)*sizeof(char),1);
                memcpy((void *)ag,(const void*)&p[bpos],length);
                if (!ad_groups) {
                    debug((char *) "%s| %s: ERR: No space to store groups\n",
                          LogTime(), PROGRAM);
                    xfree(pa);
                    xfree(ag);
                    return NULL;
                } else {
                    if (!pstrcat(ad_groups," group=")) {
                        debug((char *) "%s| %s: WARN: Too many groups ! size > %d : %s\n",
                              LogTime(), PROGRAM, MAX_PAC_GROUP_SIZE, ad_groups);
                    }
                }

                struct base64_encode_ctx ctx;
                base64_encode_init(&ctx);
                const uint32_t expectedSz = base64_encode_len(length) +1 /* terminator */;
                uint8_t *b64buf = (uint8_t *)xcalloc(expectedSz, 1);
                size_t blen = base64_encode_update(&ctx, b64buf, length, reinterpret_cast<uint8_t*>(ag));
                blen += base64_encode_final(&ctx, b64buf+blen);
                b64buf[expectedSz-1] = '\0';
                if (!pstrcat(ad_groups, reinterpret_cast<char*>(b64buf))) {
                    debug((char *) "%s| %s: WARN: Too many groups ! size > %d : %s\n",
                          LogTime(), PROGRAM, MAX_PAC_GROUP_SIZE, ad_groups);
                }
                xfree(b64buf);
                xfree(ag);

                rev = get1byt();
                bpos = bpos + 1; /* nsub */
                idauth = get6byt_be();

                snprintf(es,sizeof(es),"S-%d-%lu",rev,(long unsigned int)idauth);
                for (int k=0; k<(int)nauth; k++ ) {
                    uint32_t sauth;
                    sauth = get4byt();
                    snprintf((char *)&es[strlen(es)],sizeof(es)-strlen(es),"-%u",sauth);
                }
                debug((char *) "%s| %s: INFO: Got ExtraSid %s\n", LogTime(), PROGRAM, es);
            }
        }
        xfree(pa);
    }
    return ad_groups;
}