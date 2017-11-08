static dav_error * dav_fs_deliver(const dav_resource *resource,
                                  ap_filter_t *output)
{
    apr_pool_t *pool = resource->pool;
    apr_bucket_brigade *bb;
    apr_file_t *fd;
    apr_status_t status;
    apr_bucket *bkt;

    /* Check resource type */
    if (resource->type != DAV_RESOURCE_TYPE_REGULAR
        && resource->type != DAV_RESOURCE_TYPE_VERSION
        && resource->type != DAV_RESOURCE_TYPE_WORKING) {
        return dav_new_error(pool, HTTP_CONFLICT, 0, 0,
                             "Cannot GET this type of resource.");
    }
    if (resource->collection) {
        return dav_new_error(pool, HTTP_CONFLICT, 0, 0,
                             "There is no default response to GET for a "
                             "collection.");
    }

    if ((status = apr_file_open(&fd, resource->info->pathname,
                                APR_READ | APR_BINARY, 0,
                                pool)) != APR_SUCCESS) {
        return dav_new_error(pool, HTTP_FORBIDDEN, 0, status,
                             "File permissions deny server access.");
    }

    bb = apr_brigade_create(pool, output->c->bucket_alloc);

    apr_brigade_insert_file(bb, fd, 0, resource->info->finfo.size, pool);

    bkt = apr_bucket_eos_create(output->c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, bkt);

    if ((status = ap_pass_brigade(output, bb)) != APR_SUCCESS) {
        return dav_new_error(pool, HTTP_FORBIDDEN, 0, status,
                             "Could not write contents to filter.");
    }

    return NULL;
}