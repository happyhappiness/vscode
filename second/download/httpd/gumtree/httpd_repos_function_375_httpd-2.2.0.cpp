static dav_error *dav_really_open_db(dav_propdb *propdb, int ro)
{
    dav_error *err;

    /* we're trying to open the db; turn off the 'deferred' flag */
    propdb->deferred = 0;

    /* ask the DB provider to open the thing */
    err = (*propdb->db_hooks->open)(propdb->p, propdb->resource, ro,
                                    &propdb->db);
    if (err != NULL) {
        return dav_push_error(propdb->p, HTTP_INTERNAL_SERVER_ERROR,
                              DAV_ERR_PROP_OPENING,
                              "Could not open the property database.",
                              err);
    }

    /*
    ** NOTE: propdb->db could be NULL if we attempted to open a readonly
    **       database that doesn't exist. If we require read/write
    **       access, then a database was created and opened.
    */

    return NULL;
}