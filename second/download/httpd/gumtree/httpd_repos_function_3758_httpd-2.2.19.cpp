static apr_status_t attr_cleanup(void *theattr)
{
    apr_procattr_t *attr = (apr_procattr_t *)theattr;    
    if (attr->user_token)
        CloseHandle(attr->user_token);
    attr->user_token = NULL;
    return APR_SUCCESS;
}