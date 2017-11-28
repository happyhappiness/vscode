char *
getdomaingids(char *ad_groups, uint32_t DomainLogonId, char **Rids, uint32_t GroupCount)
{
    if (!ad_groups) {
        debug((char *) "%s| %s: ERR: No space to store groups\n",
              LogTime(), PROGRAM);
        return NULL;
    }

    if (DomainLogonId!= 0) {
        uint32_t nauth;
        uint8_t rev;
        uint64_t idauth;
        char dli[256];
        char *ag;
        size_t length;
        int l;

        align(4);

        nauth = get4byt();

        /* prepend rids with DomainID */
        length=1+1+6+nauth*4;
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
            if (!pstrcat(ad_groups,base64_encode_bin(ag, (int)(length+4)))) {
                debug((char *) "%s| %s: WARN: Too many groups ! size > %d : %s\n",
                      LogTime(), PROGRAM, MAX_PAC_GROUP_SIZE, ad_groups);
            }
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