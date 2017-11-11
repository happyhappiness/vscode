static dav_prop_insert dav_fs_insert_prop(const dav_resource *resource,
                                          int propid, dav_prop_insert what,
                                          apr_text_header *phdr)
{
    const char *value;
    const char *s;
    apr_pool_t *p = resource->info->pool;
    const dav_liveprop_spec *info;
    int global_ns;

    /* an HTTP-date can be 29 chars plus a null term */
    /* a 64-bit size can be 20 chars plus a null term */
    char buf[DAV_TIMEBUF_SIZE];

    /*
    ** None of FS provider properties are defined if the resource does not
    ** exist. Just bail for this case.
    **
    ** Even though we state that the FS properties are not defined, the
    ** client cannot store dead values -- we deny that thru the is_writable
    ** hook function.
    */
    if (!resource->exists)
        return DAV_PROP_INSERT_NOTDEF;

    switch (propid) {
    case DAV_PROPID_creationdate:
        /*
        ** Closest thing to a creation date. since we don't actually
        ** perform the operations that would modify ctime (after we
        ** create the file), then we should be pretty safe here.
        */
        dav_format_time(DAV_STYLE_ISO8601,
                        resource->info->finfo.ctime,
                        buf);
        value = buf;
        break;

    case DAV_PROPID_getcontentlength:
        /* our property, but not defined on collection resources */
        if (resource->collection)
            return DAV_PROP_INSERT_NOTDEF;

        (void) sprintf(buf, "%" APR_OFF_T_FMT, resource->info->finfo.size);
        value = buf;
        break;

    case DAV_PROPID_getetag:
        value = dav_fs_getetag(resource);
        break;

    case DAV_PROPID_getlastmodified:
        dav_format_time(DAV_STYLE_RFC822,
                        resource->info->finfo.mtime,
                        buf);
        value = buf;
        break;

    case DAV_PROPID_FS_executable:
        /* our property, but not defined on collection resources */
        if (resource->collection)
            return DAV_PROP_INSERT_NOTDEF;

        /* our property, but not defined on this platform */
        if (!(resource->info->finfo.valid & APR_FINFO_UPROT))
            return DAV_PROP_INSERT_NOTDEF;

        /* the files are "ours" so we only need to check owner exec privs */
        if (resource->info->finfo.protection & APR_UEXECUTE)
            value = "T";
        else
            value = "F";
        break;

    default:
        /* ### what the heck was this property? */
        return DAV_PROP_INSERT_NOTDEF;
    }

    /* assert: value != NULL */

    /* get the information and global NS index for the property */
    global_ns = dav_get_liveprop_info(propid, &dav_fs_liveprop_group, &info);

    /* assert: info != NULL && info->name != NULL */

    /* DBG3("FS: inserting lp%d:%s  (local %d)", ns, scan->name, scan->ns); */

    if (what == DAV_PROP_INSERT_VALUE) {
        s = apr_psprintf(p, "<lp%d:%s>%s</lp%d:%s>" DEBUG_CR,
                         global_ns, info->name, value, global_ns, info->name);
    }
    else if (what == DAV_PROP_INSERT_NAME) {
        s = apr_psprintf(p, "<lp%d:%s/>" DEBUG_CR, global_ns, info->name);
    }
    else {
        /* assert: what == DAV_PROP_INSERT_SUPPORTED */
        s = apr_psprintf(p,
                         "<D:supported-live-property D:name=\"%s\" "
                         "D:namespace=\"%s\"/>" DEBUG_CR,
                         info->name, dav_fs_namespace_uris[info->ns]);
    }
    apr_text_append(p, phdr, s);

    /* we inserted what was asked for */
    return what;
}