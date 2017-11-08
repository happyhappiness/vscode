static APR_INLINE void* apr_malloc_dbg(size_t size, const char* filename,
                                       int linenumber)
{
    return malloc(size);
}