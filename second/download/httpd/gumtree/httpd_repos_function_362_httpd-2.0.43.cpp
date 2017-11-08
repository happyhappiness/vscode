dav_error *dav_open_propdb(request_rec *r, dav_lockdb *lockdb,
			   const dav_resource *resource,
			   int ro,
			   apr_array_header_t * ns_xlate,
			   dav_propdb **p_propdb)
{
    dav_propdb *propdb = apr_pcalloc(r->pool, sizeof(*propdb));

    *p_propdb = NULL;

#if DAV_DEBUG
    if (resource->uri == NULL) {
	return dav_new_error(r->pool, HTTP_INTERNAL_SERVER_ERROR, 0,
			     "INTERNAL DESIGN ERROR: resource must define "
			     "its URI.");
    }
#endif

    propdb->r = r;
    propdb->p = r->pool; /* ### get rid of this */
    propdb->resource = resource;
    propdb->ns_xlate = ns_xlate;

    propdb->db_hooks = DAV_GET_HOOKS_PROPDB(r);

    propdb->lockdb = lockdb;

    /* always defer actual open, to avoid expense of accessing db
     * when only live properties are involved
     */
    propdb->deferred = 1;

    /* ### what to do about closing the propdb on server failure? */

    *p_propdb = propdb;
    return NULL;
}