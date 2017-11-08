dav_get_props_result dav_get_allprops(dav_propdb *propdb, dav_prop_insert what)
{
    const dav_hooks_db *db_hooks = propdb->db_hooks;
    apr_text_header hdr = { 0 };
    apr_text_header hdr_ns = { 0 };
    dav_get_props_result result = { 0 };
    int found_contenttype = 0;
    int found_contentlang = 0;
    dav_prop_insert unused_inserted;

    /* if not just getting supported live properties,
     * scan all properties in the dead prop database
     */
    if (what != DAV_PROP_INSERT_SUPPORTED) {
        if (propdb->deferred) {
            /* ### what to do with db open error? */
            (void) dav_really_open_db(propdb, 1 /*ro*/);
        }

        /* initialize the result with some start tags... */
        apr_text_append(propdb->p, &hdr,
                        "<D:propstat>" DEBUG_CR
                        "<D:prop>" DEBUG_CR);

        /* if there ARE properties, then scan them */
        if (propdb->db != NULL) {
            dav_xmlns_info *xi = dav_xmlns_create(propdb->p);
            dav_prop_name name;

            /* define (up front) any namespaces the db might need */
            (void) (*db_hooks->define_namespaces)(propdb->db, xi);

            /* get the first property name, beginning the scan */
            (void) (*db_hooks->first_name)(propdb->db, &name);
            while (name.ns != NULL) {

                /*
                ** We also look for <DAV:getcontenttype> and
                ** <DAV:getcontentlanguage>. If they are not stored as dead
                ** properties, then we need to perform a subrequest to get
                ** their values (if any).
                */
                if (*name.ns == 'D' && strcmp(name.ns, "DAV:") == 0
                    && *name.name == 'g') {
                    if (strcmp(name.name, "getcontenttype") == 0) {
                        found_contenttype = 1;
                    }
                    else if (strcmp(name.name, "getcontentlanguage") == 0) {
                        found_contentlang = 1;
                    }
                }

                if (what == DAV_PROP_INSERT_VALUE) {
                    dav_error *err;
                    int found;

                    if ((err = (*db_hooks->output_value)(propdb->db, &name,
                                                         xi, &hdr,
                                                         &found)) != NULL) {
                        /* ### anything better to do? */
                        /* ### probably should enter a 500 error */
                        goto next_key;
                    }
                    /* assert: found == 1 */
                }
                else {
                    /* the value was not requested, so just add an empty
                       tag specifying the property name. */
                    dav_output_prop_name(propdb->p, &name, xi, &hdr);
                }

              next_key:
                (void) (*db_hooks->next_name)(propdb->db, &name);
            }

            /* all namespaces have been entered into xi. generate them into
               the output now. */
            dav_xmlns_generate(xi, &hdr_ns);

        } /* propdb->db != NULL */

        /* add namespaces for all the liveprop providers */
        dav_add_all_liveprop_xmlns(propdb->p, &hdr_ns);
    }

    /* ask the liveprop providers to insert their properties */
    dav_run_insert_all_liveprops(propdb->r, propdb->resource, what, &hdr);

    /* insert the standard properties */
    /* ### should be handling the return errors here */
    (void)dav_insert_coreprop(propdb,
                              DAV_PROPID_CORE_supportedlock, "supportedlock",
                              what, &hdr, &unused_inserted);
    (void)dav_insert_coreprop(propdb,
                              DAV_PROPID_CORE_lockdiscovery, "lockdiscovery",
                              what, &hdr, &unused_inserted);

    /* if we didn't find these, then do the whole subreq thing. */
    if (!found_contenttype) {
        /* ### should be handling the return error here */
        (void)dav_insert_coreprop(propdb,
                                  DAV_PROPID_CORE_getcontenttype,
                                  "getcontenttype",
                                  what, &hdr, &unused_inserted);
    }
    if (!found_contentlang) {
        /* ### should be handling the return error here */
        (void)dav_insert_coreprop(propdb,
                                  DAV_PROPID_CORE_getcontentlanguage,
                                  "getcontentlanguage",
                                  what, &hdr, &unused_inserted);
    }

    /* if not just reporting on supported live props,
     * terminate the result */
    if (what != DAV_PROP_INSERT_SUPPORTED) {
        apr_text_append(propdb->p, &hdr,
                        "</D:prop>" DEBUG_CR
                        "<D:status>HTTP/1.1 200 OK</D:status>" DEBUG_CR
                        "</D:propstat>" DEBUG_CR);
    }

    result.propstats = hdr.first;
    result.xmlns = hdr_ns.first;
    return result;
}