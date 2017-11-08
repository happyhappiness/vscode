static dav_prop_insert dav_core_insert_prop(const dav_resource *resource,
                                            int propid, dav_prop_insert what,
                                            apr_text_header *phdr)
{
    const char *value = NULL;
    const char *s;
    apr_pool_t *p = resource->pool;
    const dav_liveprop_spec *info;
    long global_ns;

    switch (propid)
    {
    case DAV_PROPID_resourcetype:
        { /* additional type info provided by external modules ? */
            int i;

            apr_array_header_t *extensions =
                ap_list_provider_names(p, DAV_RESOURCE_TYPE_GROUP, "0");
            ap_list_provider_names_t *entry =
                (ap_list_provider_names_t *)extensions->elts;

            for (i = 0; i < extensions->nelts; i++, entry++) {
                const dav_resource_type_provider *res_hooks =
                    dav_get_resource_type_providers(entry->provider_name);
                const char *name = NULL, *uri = NULL;

                if (!res_hooks || !res_hooks->get_resource_type)
                    continue;

                if (!res_hooks->get_resource_type(resource, &name, &uri) &&
                    name) {

                    if (!uri || !strcasecmp(uri, "DAV:"))
                        value = apr_pstrcat(p, value ? value : "",
                                            "<D:", name, "/>", NULL);
                    else
                        value = apr_pstrcat(p, value ? value : "",
                                            "<x:", name,
                                            " xmlns:x=\"", uri,
                                            "\"/>", NULL);
                }
            }
        }
        switch (resource->type) {
        case DAV_RESOURCE_TYPE_VERSION:
            if (resource->baselined) {
                value = apr_pstrcat(p, value ? value : "", "<D:baseline/>", NULL);
                break;
            }
            /* fall through */
        case DAV_RESOURCE_TYPE_REGULAR:
        case DAV_RESOURCE_TYPE_WORKING:
            if (resource->collection) {
                value = apr_pstrcat(p, value ? value : "", "<D:collection/>", NULL);
            }
            else {
                /* ### should we denote lock-null resources? */
                if (value == NULL) {
                    value = "";        /* becomes: <D:resourcetype/> */
                }
            }
            break;
        case DAV_RESOURCE_TYPE_HISTORY:
            value = apr_pstrcat(p, value ? value : "", "<D:version-history/>", NULL);
            break;
        case DAV_RESOURCE_TYPE_WORKSPACE:
            value = apr_pstrcat(p, value ? value : "", "<D:collection/>", NULL);
            break;
        case DAV_RESOURCE_TYPE_ACTIVITY:
            value = apr_pstrcat(p, value ? value : "", "<D:activity/>", NULL);
            break;

        default:
            /* ### bad juju */
            return DAV_PROP_INSERT_NOTDEF;
        }
        break;

    case DAV_PROPID_comment:
    case DAV_PROPID_creator_displayname:
    case DAV_PROPID_displayname:
    case DAV_PROPID_source:
    default:
        /*
        ** This property is known, but not defined as a liveprop. However,
        ** it may be a dead property.
        */
        return DAV_PROP_INSERT_NOTDEF;
    }

    /* assert: value != NULL */

    /* get the information and global NS index for the property */
    global_ns = dav_get_liveprop_info(propid, &dav_core_liveprop_group, &info);

    /* assert: info != NULL && info->name != NULL */

    if (what == DAV_PROP_INSERT_SUPPORTED) {
        s = apr_psprintf(p,
                         "<D:supported-live-property D:name=\"%s\" "
                         "D:namespace=\"%s\"/>" DEBUG_CR,
                         info->name, dav_core_namespace_uris[info->ns]);
    }
    else if (what == DAV_PROP_INSERT_VALUE && *value != '\0') {
        s = apr_psprintf(p, "<lp%ld:%s>%s</lp%ld:%s>" DEBUG_CR,
                         global_ns, info->name, value, global_ns, info->name);
    }
    else {
        s = apr_psprintf(p, "<lp%ld:%s/>" DEBUG_CR, global_ns, info->name);
    }
    apr_text_append(p, phdr, s);

    /* we inserted what was asked for */
    return what;
}