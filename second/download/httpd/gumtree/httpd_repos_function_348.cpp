static dav_error *dav_gen_supported_live_props(request_rec *r,
                                               const dav_resource *resource,
                                               const apr_xml_elem *elem,
                                               apr_text_header *body)
{
    dav_lockdb *lockdb;
    dav_propdb *propdb;
    apr_xml_elem *child;
    apr_xml_attr *attr;
    dav_error *err;

    /* open lock database, to report on supported lock properties */
    /* ### should open read-only */
    if ((err = dav_open_lockdb(r, 0, &lockdb)) != NULL) {
        return dav_push_error(r->pool, err->status, 0,
                              "The lock database could not be opened, "
                              "preventing the reporting of supported lock "
                              "properties.",
                              err);
    }

    /* open the property database (readonly) for the resource */
    if ((err = dav_open_propdb(r, lockdb, resource, 1, NULL,
                               &propdb)) != NULL) {
        if (lockdb != NULL)
            (*lockdb->hooks->close_lockdb)(lockdb);

        return dav_push_error(r->pool, err->status, 0,
                              "The property database could not be opened, "
                              "preventing report of supported properties.",
                              err);
    }

    apr_text_append(r->pool, body, "<D:supported-live-property-set>" DEBUG_CR);

    if (elem->first_child == NULL) {
        /* show all supported live properties */
        dav_get_props_result props = dav_get_allprops(propdb, DAV_PROP_INSERT_SUPPORTED);
        body->last->next = props.propstats;
        while (body->last->next != NULL)
            body->last = body->last->next;
    }
    else {
        /* check for support of specific live property */
        for (child = elem->first_child; child != NULL; child = child->next) {
            if (child->ns == APR_XML_NS_DAV_ID
                && strcmp(child->name, "supported-live-property") == 0) {
                const char *name = NULL;
                const char *nmspace = NULL;

                /* go through attributes to find name and namespace */
                for (attr = child->attr; attr != NULL; attr = attr->next) {
                    if (attr->ns == APR_XML_NS_DAV_ID) {
                        if (strcmp(attr->name, "name") == 0)
                            name = attr->value;
                        else if (strcmp(attr->name, "namespace") == 0)
                            nmspace = attr->value;
                    }
                }

                if (name == NULL) {
                    err = dav_new_error(r->pool, HTTP_BAD_REQUEST, 0, 0,
                                        "A DAV:supported-live-property "
                                        "element does not have a \"name\" "
                                        "attribute");
                    break;
                }

                /* default namespace to DAV: */
                if (nmspace == NULL)
                    nmspace = "DAV:";

                /* check for support of property */
                dav_get_liveprop_supported(propdb, nmspace, name, body);
            }
        }
    }

    apr_text_append(r->pool, body, "</D:supported-live-property-set>" DEBUG_CR);

    dav_close_propdb(propdb);

    if (lockdb != NULL)
        (*lockdb->hooks->close_lockdb)(lockdb);

    return err;
}