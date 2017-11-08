static apr_status_t setdbit(apr_sdbm_t *db, long dbit)
{
    register long c;
    register long dirb;
    apr_status_t status;
    apr_off_t off;

    c = dbit / BYTESIZ;
    dirb = c / DBLKSIZ;

    if (dirb != db->dirbno) {
        if ((status = read_from(db->dirf, db->dirbuf, OFF_DIR(dirb), DBLKSIZ))
                    != APR_SUCCESS)
            return status;

        db->dirbno = dirb;
        
        debug(("dir read: %d\n", dirb));
    }

    db->dirbuf[c % DBLKSIZ] |= (1 << dbit % BYTESIZ);

    if (dbit >= db->maxbno)
        db->maxbno += DBLKSIZ * BYTESIZ;

    off = OFF_DIR(dirb);
    if ((status = apr_file_seek(db->dirf, APR_SET, &off)) == APR_SUCCESS)
        status = apr_file_write_full(db->dirf, db->dirbuf, DBLKSIZ, NULL);

    return status;
}