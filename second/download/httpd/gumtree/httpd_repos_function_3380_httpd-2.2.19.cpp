static apr_status_t runTest(struct testSet *ts, struct testResult *res,
                            apr_pool_t *pool)
{
    char *buffer;
    apr_status_t rv;
    int i;
    apr_size_t sz = ts->size * TEST_SIZE;
    
    buffer = apr_palloc(pool, sz);
    if (!buffer) {
        reportError("Unable to allocate buffer", ENOMEM, pool);
        return ENOMEM;
    }
    memset(buffer, ts->c, sz);

    res->iters = ts->iters > MAX_ITERS ? MAX_ITERS : ts->iters;

    for (i = 0; i < res->iters; i++) {
        apr_time_t iterTime;
        rv = sendRecvBuffer(&iterTime, buffer, sz, pool);
        if (rv != APR_SUCCESS) {
            res->iters = i;
            break;
        }
        res->msecs[i] = iterTime;
    }

    return rv;
}