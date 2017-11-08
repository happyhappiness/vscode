static apr_status_t makroom(apr_sdbm_t *db, long hash, int need)
{
    long newp;
    char twin[PBLKSIZ];
    char *pag = db->pagbuf;
    char *new = twin;
    register int smax = SPLTMAX;
    apr_status_t status;

    do {
        /*
         * split the current page
         */
        (void) splpage(pag, new, db->hmask + 1);
        /*
         * address of the new page
         */
        newp = (hash & db->hmask) | (db->hmask + 1);

        /*
         * write delay, read avoidence/cache shuffle:
         * select the page for incoming pair: if key is to go to the new page,
         * write out the previous one, and copy the new one over, thus making
         * it the current page. If not, simply write the new page, and we are
         * still looking at the page of interest. current page is not updated
         * here, as sdbm_store will do so, after it inserts the incoming pair.
         */
        if (hash & (db->hmask + 1)) {
            if ((status = write_page(db, db->pagbuf, db->pagbno)) 
                        != APR_SUCCESS)
                return status;
                    
            db->pagbno = newp;
            (void) memcpy(pag, new, PBLKSIZ);
        }
        else {
            if ((status = write_page(db, new, newp)) != APR_SUCCESS)
                return status;
        }

        if ((status = setdbit(db, db->curbit)) != APR_SUCCESS)
            return status;
        /*
         * see if we have enough room now
         */
        if (fitpair(pag, need))
            return APR_SUCCESS;
        /*
         * try again... update curbit and hmask as getpage would have
         * done. because of our update of the current page, we do not
         * need to read in anything. BUT we have to write the current
         * [deferred] page out, as the window of failure is too great.
         */
        db->curbit = 2 * db->curbit
                   + ((hash & (db->hmask + 1)) ? 2 : 1);
        db->hmask |= db->hmask + 1;
            
        if ((status = write_page(db, db->pagbuf, db->pagbno))
                    != APR_SUCCESS)
            return status;
            
    } while (--smax);

    /*
     * if we are here, this is real bad news. After SPLTMAX splits,
     * we still cannot fit the key. say goodnight.
     */
#if 0
    (void) write(2, "sdbm: cannot insert after SPLTMAX attempts.\n", 44);
#endif
    /* ### ENOSPC not really appropriate but better than nothing */
    return APR_ENOSPC;

}