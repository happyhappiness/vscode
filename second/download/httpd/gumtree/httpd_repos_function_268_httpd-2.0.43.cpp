int dav_get_resource_state(request_rec *r, const dav_resource *resource)
{
    const dav_hooks_locks *hooks = DAV_GET_HOOKS_LOCKS(r);

    if (resource->exists)
	return DAV_RESOURCE_EXISTS;

    if (hooks != NULL) {
	dav_error *err;
	dav_lockdb *lockdb;
	int locks_present;

	/*
	** A locknull resource has the form:
	**
	**   known-dir "/" locknull-file
	**
	** It would be nice to look into <resource> to verify this form,
	** but it does not have enough information for us. Instead, we
	** can look at the path_info. If the form does not match, then
	** there is no way we could have a locknull resource -- it must
	** be a plain, null resource.
	**
	** Apache sets r->filename to known-dir/unknown-file and r->path_info
	** to "" for the "proper" case. If anything is in path_info, then
	** it can't be a locknull resource.
	**
	** ### I bet this path_info hack doesn't work for repositories.
	** ### Need input from repository implementors! What kind of
	** ### restructure do we need? New provider APIs?
	*/
	if (r->path_info != NULL && *r->path_info != '\0') {
	    return DAV_RESOURCE_NULL;
	}
	
        if ((err = (*hooks->open_lockdb)(r, 1, 1, &lockdb)) == NULL) {
	    /* note that we might see some expired locks... *shrug* */
	    err = (*hooks->has_locks)(lockdb, resource, &locks_present);
	    (*hooks->close_lockdb)(lockdb);
        }

        if (err != NULL) {
	    /* ### don't log an error. return err. add higher-level desc. */

	    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
		          "Failed to query lock-null status for %s",
			  r->filename);

	    return DAV_RESOURCE_ERROR;
        }

	if (locks_present)
	    return DAV_RESOURCE_LOCK_NULL;
    }

    return DAV_RESOURCE_NULL;
}