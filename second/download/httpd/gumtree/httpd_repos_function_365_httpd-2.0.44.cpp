dav_get_props_result dav_get_props(dav_propdb *propdb, apr_xml_doc *doc)
{
    const dav_hooks_db *db_hooks = propdb->db_hooks;
    apr_xml_elem *elem = dav_find_child(doc->root, "prop");
    apr_text_header hdr_good = { 0 };
    apr_text_header hdr_bad = { 0 };
    apr_text_header hdr_ns = { 0 };
    int have_good = 0;
    dav_get_props_result result = { 0 };
    char *marks_liveprop;
    dav_xmlns_info *xi;
    int xi_filled = 0;

    /* ### NOTE: we should pass in TWO buffers -- one for keys, one for
       the marks */

    /* we will ALWAYS provide a "good" result, even if it is EMPTY */
    apr_text_append(propdb->p, &hdr_good,
                   "<D:propstat>" DEBUG_CR
                   "<D:prop>" DEBUG_CR);

    /* ### the marks should be in a buffer! */
    /* allocate zeroed-memory for the marks. These marks indicate which
       liveprop namespaces we've generated into the output xmlns buffer */

    /* same for the liveprops */
    marks_liveprop = apr_pcalloc(propdb->p, dav_get_liveprop_ns_count() + 1);

    xi = dav_xmlns_create(propdb->p);

    for (elem = elem->first_child; elem; elem = elem->next) {
        dav_elem_private *priv;
        dav_error *err;
        dav_prop_insert inserted;
        dav_prop_name name;

        /*
        ** First try live property providers; if they don't handle
        ** the property, then try looking it up in the propdb.
        */

        if (elem->priv == NULL) {
            elem->priv = apr_pcalloc(propdb->p, sizeof(*priv));
        }
        priv = elem->priv;

        /* cache the propid; dav_get_props() could be called many times */
        if (priv->propid == 0)
            dav_find_liveprop(propdb, elem);

        if (priv->propid != DAV_PROPID_CORE_UNKNOWN) {

            /* insert the property. returns 1 if an insertion was done. */
            if ((err = dav_insert_liveprop(propdb, elem, DAV_PROP_INSERT_VALUE,
                                           &hdr_good, &inserted)) != NULL) {
                /* ### need to propagate the error to the caller... */
                /* ### skip it for now, as if nothing was inserted */
            }
            if (inserted == DAV_PROP_INSERT_VALUE) {
                have_good = 1;

                /*
                ** Add the liveprop's namespace URIs. Note that provider==NULL
                ** for core properties.
                */
                if (priv->provider != NULL) {
                    const char * const * scan_ns_uri;

                    for (scan_ns_uri = priv->provider->namespace_uris;
                         *scan_ns_uri != NULL;
                         ++scan_ns_uri) {
                        int ns;

                        ns = dav_get_liveprop_ns_index(*scan_ns_uri);
                        if (marks_liveprop[ns])
                            continue;
                        marks_liveprop[ns] = 1;

                        dav_insert_xmlns(propdb->p, "lp", ns, *scan_ns_uri,
                                         &hdr_ns);
                    }
                }

                /* property added. move on to the next property. */
                continue;
            }
            else if (inserted == DAV_PROP_INSERT_NOTDEF) {
                /* nothing to do. fall thru to allow property to be handled
                   as a dead property */
            }
#if DAV_DEBUG
            else {
#if 0
                /* ### need to change signature to return an error */
                return dav_new_error(propdb->p, HTTP_INTERNAL_SERVER_ERROR, 0,
                                     "INTERNAL DESIGN ERROR: insert_liveprop "
                                     "did not insert what was asked for.");
#endif
            }
#endif
        }

        /* The property wasn't a live property, so look in the dead property
           database. */

        /* make sure propdb is really open */
        if (propdb->deferred) {
            /* ### what to do with db open error? */
            (void) dav_really_open_db(propdb, 1 /*ro*/);
        }

        if (elem->ns == APR_XML_NS_NONE)
            name.ns = "";
        else
            name.ns = APR_XML_GET_URI_ITEM(propdb->ns_xlate, elem->ns);
        name.name = elem->name;

        /* only bother to look if a database exists */
        if (propdb->db != NULL) {
            int found;

            if ((err = (*db_hooks->output_value)(propdb->db, &name,
                                                 xi, &hdr_good,
                                                 &found)) != NULL) {
                /* ### what to do? continue doesn't seem right... */
                continue;
            }

            if (found) {
                have_good = 1;

                /* if we haven't added the db's namespaces, then do so... */
                if (!xi_filled) {
                    (void) (*db_hooks->define_namespaces)(propdb->db, xi);
                    xi_filled = 1;
                }
                continue;
            }
        }

        /* not found as a live OR dead property. add a record to the "bad"
           propstats */

        /* make sure we've started our "bad" propstat */
        if (hdr_bad.first == NULL) {
            apr_text_append(propdb->p, &hdr_bad,
                            "<D:propstat>" DEBUG_CR
                            "<D:prop>" DEBUG_CR);
        }

        /* output this property's name (into the bad propstats) */
        dav_output_prop_name(propdb->p, &name, xi, &hdr_bad);
    }

    apr_text_append(propdb->p, &hdr_good,
                    "</D:prop>" DEBUG_CR
                    "<D:status>HTTP/1.1 200 OK</D:status>" DEBUG_CR
                    "</D:propstat>" DEBUG_CR);

    /* default to start with the good */
    result.propstats = hdr_good.first;

    /* we may not have any "bad" results */
    if (hdr_bad.first != NULL) {
        /* "close" the bad propstat */
        apr_text_append(propdb->p, &hdr_bad,
                        "</D:prop>" DEBUG_CR
                        "<D:status>HTTP/1.1 404 Not Found</D:status>" DEBUG_CR
                        "</D:propstat>" DEBUG_CR);

        /* if there are no good props, then just return the bad */
        if (!have_good) {
            result.propstats = hdr_bad.first;
        }
        else {
            /* hook the bad propstat to the end of the good one */
            hdr_good.last->next = hdr_bad.first;
        }
    }

    /* add in all the various namespaces, and return them */
    dav_xmlns_generate(xi, &hdr_ns);
    result.xmlns = hdr_ns.first;

    return result;
}