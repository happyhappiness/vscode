static void dav_find_liveprop(dav_propdb *propdb, apr_xml_elem *elem)
{
    const char *ns_uri;
    dav_elem_private *priv = elem->priv;
    const dav_hooks_liveprop *hooks;


    if (elem->ns == APR_XML_NS_NONE)
        ns_uri = NULL;
    else if (elem->ns == APR_XML_NS_DAV_ID)
        ns_uri = "DAV:";
    else
        ns_uri = APR_XML_GET_URI_ITEM(propdb->ns_xlate, elem->ns);

    priv->propid = dav_find_liveprop_provider(propdb, ns_uri, elem->name,
                                              &hooks);

    /* ### this test seems redundant... */
    if (priv->propid != DAV_PROPID_CORE_UNKNOWN) {
        priv->provider = hooks;
    }
}