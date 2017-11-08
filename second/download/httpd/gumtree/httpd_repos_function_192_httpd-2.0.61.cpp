static int dav_fs_is_parent_resource(
    const dav_resource *res1,
    const dav_resource *res2)
{
    dav_resource_private *ctx1 = res1->info;
    dav_resource_private *ctx2 = res2->info;
    apr_size_t len1 = strlen(ctx1->pathname);
    apr_size_t len2;

    if (res1->hooks != res2->hooks)
        return 0;

    /* it is safe to use ctx2 now */
    len2 = strlen(ctx2->pathname);

    return (len2 > len1
            && memcmp(ctx1->pathname, ctx2->pathname, len1) == 0
            && ctx2->pathname[len1] == '/');
}