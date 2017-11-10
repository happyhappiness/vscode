static int dav_rw_liveprop(dav_propdb *propdb, dav_elem_private *priv)
{
    int propid = priv->propid;

    /*
    ** Check the liveprop provider (if this is a provider-defined prop)
    */
    if (priv->provider != NULL) {
        return (*priv->provider->is_writable)(propdb->resource, propid);
    }

    /* these are defined as read-only */
    if (propid == DAV_PROPID_CORE_lockdiscovery
#if DAV_DISABLE_WRITABLE_PROPS
        || propid == DAV_PROPID_CORE_getcontenttype
        || propid == DAV_PROPID_CORE_getcontentlanguage
#endif
        || propid == DAV_PROPID_CORE_supportedlock
        ) {

        return 0;
    }

    /* these are defined as read/write */
    if (propid == DAV_PROPID_CORE_getcontenttype
        || propid == DAV_PROPID_CORE_getcontentlanguage
        || propid == DAV_PROPID_CORE_UNKNOWN) {

        return 1;
    }

    /*
    ** We don't recognize the property, so it must be dead (and writable)
    */
    return 1;
}