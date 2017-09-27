        apr_dbm_close(dbm);

        if (keyidx < KEYMAX)
            break;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "DBM socache expiry: "
                 "old: %d, new: %d, removed: %d",
                 elts, elts-deleted, deleted);
}

static void socache_dbm_status(ap_socache_instance_t *ctx, request_rec *r, 
                               int flags)
{
    apr_dbm_t *dbm;
    apr_datum_t dbmkey;
    apr_datum_t dbmval;
    int elts;
