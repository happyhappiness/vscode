static int file_make_mmap(apr_bucket *e, apr_size_t filelength,
                           apr_off_t fileoffset, apr_pool_t *p)
{
    apr_bucket_file *a = e->data;
    apr_mmap_t *mm;

    if (!a->can_mmap) {
        return 0;
    }

    if (filelength > APR_MMAP_LIMIT) {
        if (apr_mmap_create(&mm, a->fd, fileoffset, APR_MMAP_LIMIT,
                            APR_MMAP_READ, p) != APR_SUCCESS)
        {
            return 0;
        }
        apr_bucket_split(e, APR_MMAP_LIMIT);
        filelength = APR_MMAP_LIMIT;
    }
    else if ((filelength < APR_MMAP_THRESHOLD) ||
             (apr_mmap_create(&mm, a->fd, fileoffset, filelength,
                              APR_MMAP_READ, p) != APR_SUCCESS))
    {
        return 0;
    }
    apr_bucket_mmap_make(e, mm, 0, filelength);
    file_bucket_destroy(a);
    return 1;
}