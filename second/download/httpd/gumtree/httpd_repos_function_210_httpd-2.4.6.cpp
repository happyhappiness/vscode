static apr_datum_t dav_fs_build_key(apr_pool_t *p,
                                    const dav_resource *resource)
{
    const char *pathname = dav_fs_pathname(resource);
    apr_datum_t key;

    /* ### does this allocation have a proper lifetime? need to check */
    /* ### can we use a buffer for this? */

    /* size is TYPE + pathname + null */
    key.dsize = strlen(pathname) + 2;
    key.dptr = apr_palloc(p, key.dsize);
    *key.dptr = DAV_TYPE_FNAME;
    memcpy(key.dptr + 1, pathname, key.dsize - 1);
    if (key.dptr[key.dsize - 2] == '/')
        key.dptr[--key.dsize - 1] = '\0';
    return key;
}