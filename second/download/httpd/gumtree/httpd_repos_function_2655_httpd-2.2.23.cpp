static int getdbit(apr_sdbm_t *db, long dbit)
{
    register long c;
    register long dirb;

    c = dbit / BYTESIZ;
    dirb = c / DBLKSIZ;

    if (dirb != db->dirbno) {
        if (read_from(db->dirf, db->dirbuf, OFF_DIR(dirb), DBLKSIZ)
                    != APR_SUCCESS)
            return 0;

        db->dirbno = dirb;

        debug(("dir read: %d\n", dirb));
    }

    return db->dirbuf[c % DBLKSIZ] & (1 << dbit % BYTESIZ);
}