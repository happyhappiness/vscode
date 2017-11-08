static void dav_do_prop_subreq(dav_propdb *propdb)
{
    /* need to escape the uri that's in the resource struct because during
     * the property walker it's not encoded. */
    const char *e_uri = ap_escape_uri(propdb->resource->pool,
                                      propdb->resource->uri);

    /* perform a "GET" on the resource's URI (note that the resource
       may not correspond to the current request!). */
    propdb->subreq = ap_sub_req_lookup_uri(e_uri, propdb->r, NULL);
}