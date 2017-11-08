static apr_status_t getpage(apr_sdbm_t *db, long hash)
{
    register int hbit;
    register long dbit;
    register long pagb;
    apr_status_t status;

    dbit = 0;
    hbit = 0;
    while (dbit < db->maxbno && getdbit(db, dbit))
    dbit = 2 * dbit + ((hash & (1 << hbit++)) ? 2 : 1);

    debug(("dbit: %d...", dbit));

    db->curbit = dbit;
    db->hmask = masks[hbit];

    pagb = hash & db->hmask;
    /*
     * see if the block we need is already in memory.
     * note: this lookaside cache has about 10% hit rate.
     */
    if (pagb != db->pagbno) { 
        /*
         * note: here, we assume a "hole" is read as 0s.
         * if not, must zero pagbuf first.
         * ### joe: this assumption was surely never correct? but
         * ### we make it so in read_from anyway.
         */
        if ((status = read_from(db->pagf, db->pagbuf, OFF_PAG(pagb), PBLKSIZ)) 
                    != APR_SUCCESS)
            return status;

        if (!chkpage(db->pagbuf))
            return APR_ENOSPC; /* ### better error? */
        db->pagbno = pagb;

        debug(("pag read: %d\n", pagb));
    }
    return APR_SUCCESS;
}