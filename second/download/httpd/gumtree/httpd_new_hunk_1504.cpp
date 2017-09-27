    if (!opaque_cntr) {
        return NULL;
    }

    apr_global_mutex_lock(opaque_lock);
    op = (*opaque_cntr)++;
    apr_global_mutex_unlock(opaque_lock);

    if (!(entry = add_client(op, &new_entry, r->server))) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: failed to allocate client entry - ignoring "
                      "client");
        return NULL;
