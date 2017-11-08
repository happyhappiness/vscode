static apr_status_t file_bucket_setaside(apr_bucket *data, apr_pool_t *reqpool)
{
    apr_bucket_file *a = data->data;
    apr_file_t *fd = NULL;
    apr_file_t *f = a->fd;
    apr_pool_t *curpool = apr_file_pool_get(f);

    if (apr_pool_is_ancestor(curpool, reqpool)) {
        return APR_SUCCESS;
    }

    if (!apr_pool_is_ancestor(a->readpool, reqpool)) {
        a->readpool = reqpool;
    }

    apr_file_setaside(&fd, f, reqpool);
    a->fd = fd;
    return APR_SUCCESS;
}