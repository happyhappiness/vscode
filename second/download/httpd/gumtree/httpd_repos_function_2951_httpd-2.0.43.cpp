static apr_status_t open_nt_process_pipe(apr_file_t **read, apr_file_t **write,
                                         apr_int32_t iBlockingMode,
                                         apr_pool_t *pool)
{
    apr_status_t stat;
    BOOLEAN bAsyncRead, bAsyncWrite;

    switch (iBlockingMode) {
    case APR_FULL_BLOCK:
        bAsyncRead = bAsyncWrite = FALSE;
        break;
    case APR_PARENT_BLOCK:
        bAsyncRead = FALSE;
        bAsyncWrite = TRUE;
        break;
    case APR_CHILD_BLOCK:
        bAsyncRead = TRUE;
        bAsyncWrite = FALSE;
        break;
    default:
        bAsyncRead = TRUE;
        bAsyncWrite = TRUE;
    }
    if ((stat = apr_create_nt_pipe(read, write, bAsyncRead, bAsyncWrite,
                                   pool)) != APR_SUCCESS)
        return stat;

    return APR_SUCCESS;
}