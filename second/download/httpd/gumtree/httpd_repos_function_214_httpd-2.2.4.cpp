apr_pool_t *dav_fs_pool(const dav_resource *resource)
{
    return resource->info->pool;
}