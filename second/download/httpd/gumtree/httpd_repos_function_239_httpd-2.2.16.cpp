static dav_error * dav_fs_set_headers(request_rec *r,
                                      const dav_resource *resource)
{
    /* ### this function isn't really used since we have a get_pathname */
    if (!resource->exists)
        return NULL;

    /* make sure the proper mtime is in the request record */
    ap_update_mtime(r, resource->info->finfo.mtime);

    /* ### note that these use r->filename rather than <resource> */
    ap_set_last_modified(r);
    ap_set_etag(r);

    /* we accept byte-ranges */
    apr_table_setn(r->headers_out, "Accept-Ranges", "bytes");

    /* set up the Content-Length header */
    ap_set_content_length(r, resource->info->finfo.size);

    /* ### how to set the content type? */
    /* ### until this is resolved, the Content-Type header is busted */

    return NULL;
}