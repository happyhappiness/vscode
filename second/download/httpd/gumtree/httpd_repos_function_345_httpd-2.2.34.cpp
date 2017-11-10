static dav_error *dav_gen_supported_reports(request_rec *r,
                                            const dav_resource *resource,
                                            const apr_xml_elem *elem,
                                            const dav_hooks_vsn *vsn_hooks,
                                            apr_text_header *body)
{
    apr_xml_elem *child;
    apr_xml_attr *attr;
    dav_error *err;
    char *s;

    apr_text_append(r->pool, body, "<D:supported-report-set>" DEBUG_CR);

    if (vsn_hooks != NULL) {
        const dav_report_elem *reports;
        const dav_report_elem *rp;

        if ((err = (*vsn_hooks->avail_reports)(resource, &reports)) != NULL) {
            return dav_push_error(r->pool, err->status, 0,
                                  "DAV:supported-report-set could not be "
                                  "determined due to a problem fetching the "
                                  "available reports for this resource.",
                                  err);
        }

        if (reports != NULL) {
            if (elem->first_child == NULL) {
                /* show all supported reports */
                for (rp = reports; rp->nmspace != NULL; ++rp) {
                    /* Note: we presume reports->namespace is
                     * properly XML/URL quoted */
                    s = apr_psprintf(r->pool,
                                     "<D:supported-report D:name=\"%s\" "
                                     "D:namespace=\"%s\"/>" DEBUG_CR,
                                     rp->name, rp->nmspace);
                    apr_text_append(r->pool, body, s);
                }
            }
            else {
                /* check for support of specific report */
                for (child = elem->first_child; child != NULL; child = child->next) {
                    if (child->ns == APR_XML_NS_DAV_ID
                        && strcmp(child->name, "supported-report") == 0) {
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
                            return dav_new_error(r->pool, HTTP_BAD_REQUEST, 0,
                                                 "A DAV:supported-report element "
                                                 "does not have a \"name\" attribute");
                        }

                        /* default namespace to DAV: */
                        if (nmspace == NULL)
                            nmspace = "DAV:";

                        for (rp = reports; rp->nmspace != NULL; ++rp) {
                            if (strcmp(name, rp->name) == 0
                                && strcmp(nmspace, rp->nmspace) == 0) {
                                /* Note: we presume reports->nmspace is
                                 * properly XML/URL quoted
                                 */
                                s = apr_psprintf(r->pool,
                                                 "<D:supported-report "
                                                 "D:name=\"%s\" "
                                                 "D:namespace=\"%s\"/>"
                                                 DEBUG_CR,
                                                 rp->name, rp->nmspace);
                                apr_text_append(r->pool, body, s);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    apr_text_