static apr_datum_t dav_fs_build_key(apr_pool_t *p,
                                    const dav_resource *resource)
{
    const char *file = dav_fs_pathname(resource);
    apr_datum_t key;
    apr_finfo_t finfo;
    apr_status_t rv;

    /* ### use lstat() ?? */
    /*
     * XXX: What for platforms with no IDENT (dev/inode)?
     */
    rv = apr_stat(&finfo, file, APR_FINFO_IDENT, p);
    if ((rv == APR_SUCCESS || rv == APR_INCOMPLETE)
        && ((finfo.valid & APR_FINFO_IDENT) == APR_FINFO_IDENT))
    {
        /* ### can we use a buffer for this? */
        key.dsize = 1 + sizeof(finfo.inode) + sizeof(finfo.device);
        key.dptr = apr_palloc(p, key.dsize);
        *key.dptr = DAV_TYPE_INODE;
        memcpy(key.dptr + 1, &finfo.inode, sizeof(finfo.inode));
        memcpy(key.dptr + 1 + sizeof(finfo.inode), &finfo.device,
               sizeof(finfo.device));

        return key;
    }

    return dav_fs_build_fname_key(p, file);
}