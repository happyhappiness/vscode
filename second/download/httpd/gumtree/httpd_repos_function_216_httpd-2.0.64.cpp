static dav_error *dav_fs_patch_validate(const dav_resource *resource,
                                        const apr_xml_elem *elem,
                                        int operation,
                                        void **context,
                                        int *defer_to_dead)
{
    const apr_text *cdata;
    const apr_text *f_cdata;
    char value;
    dav_elem_private *priv = elem->priv;

    if (priv->propid != DAV_PROPID_FS_executable) {
        *defer_to_dead = 1;
        return NULL;
    }

    if (operation == DAV_PROP_OP_DELETE) {
        return dav_new_error(resource->info->pool, HTTP_CONFLICT, 0,
                             "The 'executable' property cannot be removed.");
    }

    cdata = elem->first_cdata.first;

    /* ### hmm. this isn't actually looking at all the possible text items */
    f_cdata = elem->first_child == NULL
        ? NULL
        : elem->first_child->following_cdata.first;

    /* DBG3("name=%s  cdata=%s  f_cdata=%s",elem->name,cdata ? cdata->text : "[null]",f_cdata ? f_cdata->text : "[null]"); */

    if (cdata == NULL) {
        if (f_cdata == NULL) {
            return dav_new_error(resource->info->pool, HTTP_CONFLICT, 0,
                                 "The 'executable' property expects a single "
                                 "character, valued 'T' or 'F'. There was no "
                                 "value submitted.");
        }
        cdata = f_cdata;
    }
    else if (f_cdata != NULL)
        goto too_long;

    if (cdata->next != NULL || strlen(cdata->text) != 1)
        goto too_long;

    value = cdata->text[0];
    if (value != 'T' && value != 'F') {
        return dav_new_error(resource->info->pool, HTTP_CONFLICT, 0,
                             "The 'executable' property expects a single "
                             "character, valued 'T' or 'F'. The value "
                             "submitted is invalid.");
    }

    *context = (void *)(value == 'T');

    return NULL;

  too_long:
    return dav_new_error(resource->info->pool, HTTP_CONFLICT, 0,
                         "The 'executable' property expects a single "
                         "character, valued 'T' or 'F'. The value submitted "
                         "has too many characters.");

}