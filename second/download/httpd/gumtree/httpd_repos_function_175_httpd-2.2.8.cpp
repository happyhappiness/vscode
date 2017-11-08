static dav_error * dav_generic_load_lock_record(dav_lockdb *lockdb,
                                                apr_datum_t key,
                                                int add_method,
                                                dav_lock_discovery **direct,
                                                dav_lock_indirect **indirect)
{
    apr_pool_t *p = lockdb->info->pool;
    dav_error *err;
    apr_status_t status;
    apr_size_t offset = 0;
    int need_save = DAV_FALSE;
    apr_datum_t val = { 0 };
    dav_lock_discovery *dp;
    dav_lock_indirect *ip;

    if (add_method != DAV_APPEND_LIST) {
        *direct = NULL;
        *indirect = NULL;
    }

    if ((err = dav_generic_really_open_lockdb(lockdb)) != NULL) {
        /* ### add a higher-level error? */
        return err;
    }

    /*
     * If we opened readonly and the db wasn't there, then there are no
     * locks for this resource. Just exit.
     */
    if (lockdb->info->db == NULL) {
        return NULL;
    }

    if ((status = apr_dbm_fetch(lockdb->info->db, key, &val)) != APR_SUCCESS) {
        return dav_generic_dbm_new_error(lockdb->info->db, p, status);
    }

    if (!val.dsize) {
        return NULL;
    }

    while (offset < val.dsize) {
        switch (*(val.dptr + offset++)) {
        case DAV_LOCK_DIRECT:
            /* Create and fill a dav_lock_discovery structure */

            dp = apr_pcalloc(p, sizeof(*dp));

            /* Copy the dav_lock_discovery_fixed portion */
            memcpy(dp, val.dptr + offset, sizeof(dp->f));
            offset += sizeof(dp->f);

            /* Copy the lock token. */
            dp->locktoken = apr_pmemdup(p, val.dptr + offset, sizeof(*dp->locktoken));
            offset += sizeof(*dp->locktoken);

            /* Do we have an owner field? */
            if (*(val.dptr + offset) == '\0') {
                ++offset;
            }
            else {
                apr_size_t len = strlen(val.dptr + offset);
                dp->owner = apr_pstrmemdup(p, val.dptr + offset, len);
                offset += len + 1;
            }

            if (*(val.dptr + offset) == '\0') {
                ++offset;
            }
            else {
                apr_size_t len = strlen(val.dptr + offset);
                dp->auth_user = apr_pstrmemdup(p, val.dptr + offset, len);
                offset += len + 1;
            }

            if (!dav_generic_lock_expired(dp->f.timeout)) {
                dp->next = *direct;
                *direct = dp;
            }
            else {
                need_save = DAV_TRUE;
            }
            break;

        case DAV_LOCK_INDIRECT:
            /* Create and fill a dav_lock_indirect structure */

            ip = apr_pcalloc(p, sizeof(*ip));
            ip->locktoken = apr_pmemdup(p, val.dptr + offset, sizeof(*ip->locktoken));
            offset += sizeof(*ip->locktoken);
            memcpy(&ip->timeout, val.dptr + offset, sizeof(ip->timeout));
            offset += sizeof(ip->timeout);
            /* length of datum */
            ip->key.dsize = *((int *) (val.dptr + offset));
            offset += sizeof(ip->key.dsize);
            ip->key.dptr = apr_pmemdup(p, val.dptr + offset, ip->key.dsize);
            offset += ip->key.dsize;

            if (!dav_generic_lock_expired(ip->timeout)) {
                ip->next = *indirect;
                *indirect = ip;
            }
            else {
                need_save = DAV_TRUE;
            }

            break;

        default:
            apr_dbm_freedatum(lockdb->info->db, val);

            /* ### should use a computed_desc and insert corrupt token data */
            --offset;
            return dav_new_error(p,
                                 HTTP_INTERNAL_SERVER_ERROR,
                                 DAV_ERR_LOCK_CORRUPT_DB,
                                 apr_psprintf(p,
                                             "The lock database was found to "
                                             "be corrupt. offset %"
                                             APR_SIZE_T_FMT ", c=%02x