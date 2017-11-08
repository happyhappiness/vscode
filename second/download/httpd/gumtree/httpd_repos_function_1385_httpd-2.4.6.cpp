static apr_status_t recall_body(cache_handle_t *h, apr_pool_t *p, apr_bucket_brigade *bb)
{
    disk_cache_object_t *dobj = (disk_cache_object_t*) h->cache_obj->vobj;

    if (dobj->data.fd) {
        apr_brigade_insert_file(bb, dobj->data.fd, 0, dobj->file_size, p);
    }

    return APR_SUCCESS;
}