static void dav_do_prop_subreq(dav_propdb *propdb)
{
    /* perform a "GET" on the resource's URI (note that the resource
       may not correspond to the current request!). */
    propdb->subreq = ap_sub_req_lookup_uri(propdb->resource->uri, propdb->r,
                                           NULL);
}