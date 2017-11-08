static dav_error * dav_propdb_apply_rollback(dav_db *db,
                                             dav_deadprop_rollback *rollback)
{
    if (!rollback) {
        return NULL; /* no rollback, nothing to do */
    }

    if (rollback->value.dptr == NULL) {
        /* don't fail if the thing isn't really there. */
        (void) dav_dbm_delete(db, rollback->key);
        return NULL;
    }

    return dav_dbm_store(db, rollback->key, rollback->value);
}