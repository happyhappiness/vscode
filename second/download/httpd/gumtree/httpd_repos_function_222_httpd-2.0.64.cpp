void dav_fs_insert_all_liveprops(request_rec *r, const dav_resource *resource,
                                 dav_prop_insert what, apr_text_header *phdr)
{
    /* don't insert any liveprops if this isn't "our" resource */
    if (resource->hooks != &dav_hooks_repository_fs)
        return;

    if (!resource->exists) {
        /* a lock-null resource */
        /*
        ** ### technically, we should insert empty properties. dunno offhand
        ** ### what part of the spec said this, but it was essentially thus:
        ** ### "the properties should be defined, but may have no value".
        */
        return;
    }

    (void) dav_fs_insert_prop(resource, DAV_PROPID_creationdate,
                              what, phdr);
    (void) dav_fs_insert_prop(resource, DAV_PROPID_getcontentlength,
                              what, phdr);
    (void) dav_fs_insert_prop(resource, DAV_PROPID_getlastmodified,
                              what, phdr);
    (void) dav_fs_insert_prop(resource, DAV_PROPID_getetag,
                              what, phdr);

#ifdef DAV_FS_HAS_EXECUTABLE
    /* Only insert this property if it is defined for this platform. */
    (void) dav_fs_insert_prop(resource, DAV_PROPID_FS_executable,
                              what, phdr);
#endif

    /* ### we know the others aren't defined as liveprops */
}