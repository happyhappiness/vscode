static dav_error * dav_fs_load_lock_record(dav_lockdb *lockdb, apr_datum_t key,
                                           int add_method,
                                           dav_lock_discovery **direct,
                                           dav_lock_indirect **indirect)
{
    apr_pool_t *p = lockdb->info->pool;
    dav_error *err;
    apr_size_t offset = 0;
    int need_save = DAV_FALSE;
    apr_datum_t val = { 0 };
    dav_lock_discovery *dp;
    dav_lock_indirect *ip;
    dav_buffer buf = { 0 };

    if (add_method != DAV_APPEND_LIST) {
        *direct = NULL;
        *indirect = NULL;
    }

    if ((err = dav_fs_really_open_lockdb(lockdb)) != NULL) {
        /* ### add a higher-level error? */
        return err;
    }

    /*
    ** If we opened readonly and the db wasn't there, then there are no
    ** locks for this resource. Just exit.
    */
    if (lockdb->info->db == NULL)
        return NULL;

    if ((err = dav_dbm_fetch(lockdb->info->db, key, &val)) != NULL)
        return err;

    if (!val.dsize)
        return NULL;

    while (offset < val.dsize) {
        switch (*(val.dptr + offset++)) {
        case DAV_LOCK_DIRECT:
            /* Create and fill a dav_lock_discovery structure */

            dp = apr_pcalloc(p, sizeof(*dp));
            memcpy(dp, val.dptr + offset, sizeof(dp->f));
            offset += sizeof(dp->f);
            dp->locktoken = apr_pmemdup(p, val.dptr + offset, sizeof(*dp->locktoken));
            offset += sizeof(*dp->locktoken);
            if (*(val.dptr + offset) == '\0') {
                ++offset;
            }
            else {
                dp->owner = apr_pstrdup(p, val.dptr + offset);
                offset += strlen(dp->owner) + 1;
            }

            if (*(val.dptr + offset) == '\0') {
                ++offset;
            }
            else {
                dp->auth_user = apr_pstrdup(p, val.dptr + offset);
                offset += strlen(dp->auth_user) + 1;
            }

            if (!dav_fs_lock_expired(dp->f.timeout)) {
                dp->next = *direct;
                *direct = dp;
            }
            else {
                need_save = DAV_TRUE;

                /* Remove timed-out locknull fm .locknull list */
                if (*key.dptr == DAV_TYPE_FNAME) {
                    const char *fname = key.dptr + 1;
                    apr_finfo_t finfo;
                    apr_status_t rv;

                    /* if we don't see the file, then it's a locknull */
                    rv = apr_stat(&finfo, fname, APR_FINFO_MIN | APR_FINFO_LINK, p);
                    if (rv != APR_SUCCESS && rv != APR_INCOMPLETE) {
                        if ((err = dav_fs_remove_locknull_member(p, fname, &buf)) != NULL) {
                            /* ### push a higher-level description? */
                            return err;
                        }
                    }
                }
            }
            break;

        case DAV_LOCK_INDIRECT:
            /* Create and fill a dav_lock_indirect structure */

            ip = apr_pcalloc(p, sizeof(*ip));
            ip->locktoken = apr_pmemdup(p, val.dptr + offset, sizeof(*ip->locktoken));
            offset += sizeof(*ip->locktoken);
            memcpy(&ip->timeout, val.dptr + offset, sizeof(ip->timeout));
            offset += sizeof(ip->timeout);
            memcpy(&ip->key.dsize, val.dptr + offset, sizeof(ip->key.dsize)); /* length of datum */
            offset += sizeof(ip->key.dsize);
            ip->key.dptr = apr_pmemdup(p, val.dptr + offset, ip->key.dsize);
            offset += ip->key.dsize;

            if (!dav_fs_lock_expired(ip->timeout)) {
                ip->next = *indirect;
                *indirect = ip;
            }
            else {
                need_save = DAV_TRUE;
                /* A locknull resource will never be locked indirectly */
            }

            break;

        default:
            dav_dbm_freedatum(lockdb->info->db, val);

            /* ### should use a computed_desc and insert corrupt token data */
            --offset;
            return dav_new_error(p,
                                 HTTP_INTERNAL_SERVER_ERROR,
                                 DAV_ERR_LOCK_CORRUPT_DB, 0,
                                 apr_psprintf(p,
                                             "The lock database was found to "
                                             "be corrupt. offset %"
                                             APR_SIZE_T_FMT ", c=%02x",
                                             offset, val.dptr[offset]));
        }
    }

    dav_dbm_freedatum(lockdb->info->db, val);

    /* Clean up this record if we found expired locks */
    /*
    ** ### shouldn't do this if we've been opened READONLY. elide the
    ** ### timed-out locks from the response, but don't save that info back
    */
    if (need_save == DAV_TRUE) {
        return dav_fs_save_lock_record(lockdb, key, *direct, *indirect);
    }

    return NULL;
}