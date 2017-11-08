static dav_error * dav_propdb_store(dav_db *db, const dav_prop_name *name,
                                    const apr_xml_elem *elem,
                                    dav_namespace_map *mapping)
{
    apr_datum_t key = dav_build_key(db, name);
    apr_datum_t value;

    /* Note: mapping->ns_map was set up in dav_propdb_map_namespaces() */

    /* ### use a db- subpool for these values? clear on exit? */

    /* quote all the values in the element */
    /* ### be nice to do this without affecting the element itself */
    /* ### of course, the cast indicates Badness is occurring here */
    apr_xml_quote_elem(db->pool, (apr_xml_elem *)elem);

    /* generate a text blob for the xml:lang plus the contents */
    apr_xml_to_text(db->pool, elem, APR_XML_X2T_LANG_INNER, NULL,
                    mapping->ns_map,
                    (const char **)&value.dptr, &value.dsize);

    return dav_dbm_store(db, key, value);
}