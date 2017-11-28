char *
getdomaingids(char *ad_groups, uint32_t DomainLogonId, char **Rids, uint32_t GroupCount)
{
    if (!ad_groups) {
        debug((char *) "%s| %s: ERR: No space to store groups\n",
              LogTime(), PROGRAM);
        return NULL;
    }

    if (DomainLogonId!= 0) {
        uint8_t rev;
        uint64_t idauth;
        char dli[256];
        char *ag;
        int l;

        align(4);

        uint32_t nauth = get4byt();

        // check if nauth math will produce invalid length values on 32-bit
        static uint32_t maxGidCount = (UINT32_MAX-1-1-6)/4;
        if (nauth > maxGidCount) {
            debug((char *) "%s| %s: ERROR: Too many groups ! count > %d : %s\n",
                  LogTime(), PROGRAM, maxGidCount, ad_groups);
            return NULL;
        }
        size_t length = 1+1+6+nauth*4;

        /* prepend rids with DomainID */
        for (l=0; l<(int)GroupCount; l++) {
            ag=(char *)xcalloc((length+4)*sizeof(char),1);
            memcpy((void *)ag,(const void*)&p[bpos],1);
            memcpy((void *)&ag[1],(const void*)&p[bpos+1],1);
            ag[1] = ag[1]+1;
            memcpy((void *)&ag[2],(const void*)&p[bpos+2],6+nauth*4);
            memcpy((void *)&ag[length],(const void*)Rids[l],4);
            if (l==0) {
                if (!pstrcpy(ad_groups,"group=")) {
                    debug((char *) "%s| %s: WARN: Too many groups ! size > %d : %s\n",
                          LogTime(), PROGRAM, MAX_PAC_GROUP_SIZE, ad_groups);
                }
            } else {
                if (!pstrcat(ad_groups," group=")) {
                    debug((char *) "%s| %s: WARN: Too many groups ! size > %d : %s\n",
                          LogTime(), PROGRAM, MAX_PAC_GROUP_SIZE, ad_groups);
                }
            }
            struct base64_encode_ctx ctx;
            base64_encode_init(&ctx);
            const uint32_t expectedSz = base64_encode_len(length+4) +1 /* terminator */;
            uint8_t *b64buf = (uint8_t *)xcalloc(expectedSz, 1);
            size_t blen = base64_encode_update(&ctx, b64buf, length+4, reinterpret_cast<uint8_t*>(ag));
            blen += base64_encode_final(&ctx, b64buf+blen);
            b64buf[expectedSz-1] = '\0';
            if (!pstrcat(ad_groups, reinterpret_cast<char*>(b64buf))) {
                debug((char *) "%s| %s: WARN: Too many groups ! size > %d : %s\n",
                      LogTime(), PROGRAM, MAX_PAC_GROUP_SIZE, ad_groups);
            }
            xfree(b64buf);
            xfree(ag);
        }

        /* mainly for debug only */
        rev = get1byt();
        bpos = bpos + 1; /*nsub*/
        idauth = get6byt_be();

        snprintf(dli,sizeof(dli),"S-%d-%lu",rev,(long unsigned int)idauth);
        for ( l=0; l<(int)nauth; l++ ) {
            uint32_t sauth;
            sauth = get4byt();
            snprintf((char *)&dli[strlen(dli)],sizeof(dli)-strlen(dli),"-%u",sauth);
        }
        debug((char *) "%s| %s: INFO: Got DomainLogonId %s\n", LogTime(), PROGRAM, dli);
    }
    return ad_groups;
}