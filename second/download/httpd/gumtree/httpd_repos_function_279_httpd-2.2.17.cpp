static dav_error * dav_propdb_define_namespaces(dav_db *db, dav_xmlns_info *xi)
{
    int ns;
    const char *uri = db->ns_table.buf + sizeof(dav_propdb_metadata);

    /* within the prop values, we use "ns%d" for prefixes... register them */
    for (ns = 0; ns < db->ns_count; ++ns, uri += strlen(uri) + 1) {

        /* Empty URIs signify the empty namespace. These do not get a
           namespace prefix. when we generate the value, we will simply
           leave off the prefix, which is defined by mod_dav to be the
           empty namespace. */
        if (*uri == '\0')
            continue;

        /* ns_table.buf can move, so copy its value (we want the values to
           last as long as the provided dav_xmlns_info). */
        dav_xmlns_add(xi,
                      apr_psprintf(xi->pool, "ns%d", ns),
                      apr_pstrdup(xi->pool, uri));
    }

    return NULL;
}