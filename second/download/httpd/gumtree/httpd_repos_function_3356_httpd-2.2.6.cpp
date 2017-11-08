static apr_status_t threadattr_cleanup(void *data)
{
    apr_threadattr_t *attr = data;
    apr_status_t rv;

    rv = pthread_attr_destroy(&attr->attr);
#ifdef PTHREAD_SETS_ERRNO
    if (rv) {
        rv = errno;
    }
#endif
    return rv;
}