char **
getgids(char **Rids, uint32_t GroupIds, uint32_t  GroupCount)
{
    if (GroupIds!= 0) {
        uint32_t ngroup;
        int l;

        align(4);
        ngroup = get4byt();
        if ( ngroup != GroupCount) {
            debug((char *) "%s| %s: ERROR: Group encoding error => GroupCount: %d Array size: %d\n",
                  LogTime(), PROGRAM, GroupCount, ngroup);
            return NULL;
        }
        debug((char *) "%s| %s: INFO: Found %d rids\n", LogTime(), PROGRAM, GroupCount);

        Rids=(char **)xcalloc(GroupCount*sizeof(char*),1);
        for ( l=0; l<(int)GroupCount; l++) {
            uint32_t sauth;
            Rids[l]=(char *)xcalloc(4*sizeof(char),1);
            memcpy((void *)Rids[l],(void *)&p[bpos],4);
            sauth = get4byt();
            debug((char *) "%s| %s: Info: Got rid: %u\n", LogTime(), PROGRAM, sauth);
            /* attribute */
            bpos = bpos+4;
        }
    }
    return Rids;
}