apr_status_t apr_threadattr_detach_set(apr_threadattr_t *attr,apr_int32_t on)
{
    attr->detach = on;
    return APR_SUCCESS;   
}