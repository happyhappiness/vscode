static request_rec *dav_fs_get_request_rec(const dav_resource *resource)
{
    return resource->info->r;
}