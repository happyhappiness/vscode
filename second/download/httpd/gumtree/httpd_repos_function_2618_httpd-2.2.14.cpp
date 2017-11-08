static apr_status_t getnext(apr_sdbm_datum_t *key, apr_sdbm_t *db)
{
    apr_status_t status;
    for (;;) {
        db->keyptr++;
        *key = getnkey(db->pagbuf, db->keyptr);
        if (key->dptr != NULL)
            return APR_SUCCESS;
        /*
         * we either run out, or there is nothing on this page..
         * try the next one... If we lost our position on the
         * file, we will have to seek.
         */
        db->keyptr = 0;
        if (db->pagbno != db->blkptr++) {
            apr_off_t off = OFF_PAG(db->blkptr);
            if ((status = apr_file_seek(db->pagf, APR_SET, &off))
                        != APR_SUCCESS)
                return status;
        }

        db->pagbno = db->blkptr;
        /* ### EOF acceptable here too? */
        if ((status = apr_file_read_full(db->pagf, db->pagbuf, PBLKSIZ, NULL))
                    != APR_SUCCESS)
            return status;
        if (!chkpage(db->pagbuf))
            return APR_EGENERAL;     /* ### need better error */
    }

    /* NOTREACHED */
}