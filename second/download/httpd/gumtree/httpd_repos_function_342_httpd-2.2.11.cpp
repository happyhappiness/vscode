static dav_error *dav_gen_supported_methods(request_rec *r,
                                            const apr_xml_elem *elem,
                                            const apr_table_t *methods,
                                            apr_text_header *body)
{
    const apr_array_header_t *arr;
    const apr_table_entry_t *elts;
    apr_xml_elem *child;
    apr_xml_attr *attr;
    char *s;
    int i;

    apr_text_append(r->pool, body, "<D:supported-method-set>" DEBUG_CR);

    if (elem->first_child == NULL) {
        /* show all supported methods */
        arr = apr_table_elts(methods);
        elts = (const apr_table_entry_t *)arr->elts;

        for (i = 0; i < arr->nelts; ++i) {
            if (elts[i].key == NULL)
                continue;

            s = apr_psprintf(r->pool,
                             "<D:supported-method D:name=\"%s\"/>"
                             DEBUG_CR,
                             elts[i].key);
            apr_text_append(r->pool, body, s);
        }
    }
    else {
        /* check for support of specific methods */
        for (child = elem->first_child; child != NULL; child = child->next) {
            if (child->ns == APR_XML_NS_DAV_ID
                && strcmp(child->name, "supported-method") == 0) {
                const char *name = NULL;

                /* go through attributes to find method name */
                for (attr = child->attr; attr != NULL; attr = attr->next) {
                    if (attr->ns == APR_XML_NS_DAV_ID
                        && strcmp(attr->name, "name") == 0)
                            name = attr->value;
                }

                if (name == NULL) {
                    return dav_new_error(r->pool, HTTP_BAD_REQUEST, 0,
                                         "A DAV:supported-method element "
                                         "does not have a \"name\" attribute");
                }

                /* see if method is supported */
                if (apr_table_get(methods, name) != NULL) {
                    s = apr_psprintf(r->pool,
                                     "<D:supported-method D:name=\"%s\"/>"
                                     DEBUG_CR,
                                     name);
                    apr_text_append(r->pool, body, s);
                }
            }
        }
    }

    apr_text_append(r->pool, body, "</D:supported-method-set>" DEBUG_CR);
    return NULL;
}