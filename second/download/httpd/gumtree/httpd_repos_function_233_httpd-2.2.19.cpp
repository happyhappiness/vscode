static int dav_fs_is_same_resource(
    const dav_resource *res1,
    const dav_resource *res2)
{
    dav_resource_private *ctx1 = res1->info;
    dav_resource_private *ctx2 = res2->info;

    if (res1->hooks != res2->hooks)
        return 0;

    if ((ctx1->finfo.filetype != 0) && (ctx2->finfo.filetype != 0)
        && (ctx1->finfo.valid & ctx2->finfo.valid & APR_FINFO_INODE)) {
        return ctx1->finfo.inode == ctx2->finfo.inode;
    }
    else {
        return strcmp(ctx1->pathname, ctx2->pathname) == 0;
    }
}