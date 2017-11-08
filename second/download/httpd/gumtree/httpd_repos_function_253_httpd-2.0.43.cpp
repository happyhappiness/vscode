void dav_core_insert_all_liveprops(request_rec *r,
                                   const dav_resource *resource,
                                   dav_prop_insert what, apr_text_header *phdr)
{
    (void) dav_core_insert_prop(resource, DAV_PROPID_resourcetype,
                                what, phdr);
}