char *
getextrasids(char *ad_groups, uint32_t ExtraSids, uint32_t SidCount)
{
    if (ExtraSids!= 0) {
        uint32_t ngroup;
        uint32_t *pa;
        char *ag;
        size_t length;
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
            uint32_t nauth;
            uint8_t rev;
            uint64_t idauth;
            uint32_t sauth;
            int k;

            if (pa[l] != 0) {
                nauth = get4byt();

                length = 1+1+6+nauth*4;
                ag = (char *)xcalloc((length)*sizeof(char),1);
                memcpy((void *)ag,(const void*)&p[bpos],length);
                if (!ad_groups) {
                    if (!xstrcpy(ad_groups,"group=")) {
                        debug((char *) "%s| %s: WARN: Too many groups ! size > %d : %s\n",
                              LogTime(), PROGRAM, MAX_PAC_GROUP_SIZE, ad_groups);
                    }
                } else {
                    if (!xstrcat(ad_groups," group=")) {
                        debug((char *) "%s| %s: WARN: Too many groups ! size > %d : %s\n",
                              LogTime(), PROGRAM, MAX_PAC_GROUP_SIZE, ad_groups);
                    }
                }
                if (!xstrcat(ad_groups,base64_encode_bin(ag, (int)length))) {
                    debug((char *) "%s| %s: WARN: Too many groups ! size > %d : %s\n",
                          LogTime(), PROGRAM, MAX_PAC_GROUP_SIZE, ad_groups);
                }
                xfree(ag);

                rev = get1byt();
                bpos = bpos + 1; /* nsub */
                idauth = get6byt_be();

                snprintf(es,sizeof(es),"S-%d-%lu",rev,(long unsigned int)idauth);
                for ( k=0; k<(int)nauth; k++ ) {
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