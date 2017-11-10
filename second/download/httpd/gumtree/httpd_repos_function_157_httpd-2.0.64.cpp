static dav_lock *dav_fs_alloc_lock(dav_lockdb *lockdb, apr_datum_t key,
				   const dav_locktoken *locktoken)
{
    dav_lock_combined *comb;

    comb = apr_pcalloc(lockdb->info->pool, sizeof(*comb));
    comb->pub.rectype = DAV_LOCKREC_DIRECT;
    comb->pub.info = &comb->priv;
    comb->priv.key = key;

    if (locktoken == NULL) {
	comb->pub.locktoken = &comb->token;
        apr_uuid_get(&comb->token.uuid);
    }
    else {
	comb->pub.locktoken = locktoken;
    }

    return &comb->pub;
}