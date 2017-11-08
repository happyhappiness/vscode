void dav_get_liveprop_supported(dav_propdb *propdb,
                                const char *ns_uri,
                                const char *propname,
                                apr_text_header *body)
{
    int propid;
    const dav_hooks_liveprop *hooks;

    propid = dav_find_liveprop_provider(propdb, ns_uri, propname, &hooks);

    if (propid != DAV_PROPID_CORE_UNKNOWN) {
        if (hooks == NULL) {
            /* this is a "core" property that we define */
            dav_prop_insert unused_inserted;
            dav_insert_coreprop(propdb, propid, propname,
                                DAV_PROP_INSERT_SUPPORTED, body, &unused_inserted);
        }
        else {
            (*hooks->insert_prop)(propdb->resource, propid,
                                  DAV_PROP_INSERT_SUPPORTED, body);
        }
    }
}