static int dav_find_liveprop_provider(dav_propdb *propdb,
                                      const char *ns_uri,
                                      const char *propname,
                                      const dav_hooks_liveprop **provider)
{
    int propid;

    *provider = NULL;

    if (ns_uri == NULL) {
        /* policy: liveprop providers cannot define no-namespace properties */
        return DAV_PROPID_CORE_UNKNOWN;
    }

    /* check liveprop providers first, so they can define core properties */
    propid = dav_run_find_liveprop(propdb->resource, ns_uri, propname,
                                   provider);
    if (propid != 0) {
        return propid;
    }

    /* check for core property */
    if (strcmp(ns_uri, "DAV:") == 0) {
        const char * const *p = dav_core_props;

        for (propid = DAV_PROPID_CORE; *p != NULL; ++p, ++propid)
            if (strcmp(propname, *p) == 0) {
                return propid;
            }
    }

    /* no provider for this property */
    return DAV_PROPID_CORE_UNKNOWN;
}