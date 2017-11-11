static dav_error * dav_propdb_map_namespaces(
    dav_db *db,
    const apr_array_header_t *namespaces,
    dav_namespace_map **mapping)
{
    dav_namespace_map *m = apr_palloc(db->pool, sizeof(*m));
    int i;
    int *pmap;
    const char **puri;

    /*
    ** Iterate over the provided namespaces. If a namespace already appears
    ** in our internal map of URI -> ns_id, then store that in the map. If
    ** we don't know the namespace yet, then add it to the map and to our
    ** table of known namespaces.
    */
    m->ns_map = pmap = apr_palloc(db->pool, namespaces->nelts * sizeof(*pmap));
    for (i = namespaces->nelts, puri = (const char **)namespaces->elts;
         i-- > 0;
         ++puri, ++pmap) {

        const char *uri = *puri;
        apr_size_t uri_len = strlen(uri);
        long ns_id = (long)apr_hash_get(db->uri_index, uri, uri_len);

        if (ns_id == 0) {
            dav_check_bufsize(db->pool, &db->ns_table, uri_len + 1);
            memcpy(db->ns_table.buf + db->ns_table.cur_len, uri, uri_len + 1);
            db->ns_table.cur_len += uri_len + 1;

            /* copy the uri in case the passed-in namespaces changes in
               some way. */
            apr_hash_set(db->uri_index, apr_pstrdup(db->pool, uri), uri_len,
                         (void *)((long)(db->ns_count + 1)));

            db->ns_table_dirty = 1;

            *pmap = db->ns_count++;
        }
        else {
            *pmap = ns_id - 1;
        }
    }

    *mapping = m;
    return NULL;
}