static dav_error * dav_insert_liveprop(dav_propdb *propdb,
                                       const apr_xml_elem *elem,
                                       dav_prop_insert what,
                                       apr_text_header *phdr,
                                       dav_prop_insert *inserted)
{
    dav_elem_private *priv = elem->priv;

    *inserted = DAV_PROP_INSERT_NOTDEF;

    if (priv->provider == NULL) {
        /* this is a "core" property that we define */
        return dav_insert_coreprop(propdb, priv->propid, elem->name,
                                   what, phdr, inserted);
    }

    /* ask the provider (that defined this prop) to insert the prop */
    *inserted = (*priv->provider->insert_prop)(propdb->resource, priv->propid,
                                               what, phdr);

    return NULL;
}