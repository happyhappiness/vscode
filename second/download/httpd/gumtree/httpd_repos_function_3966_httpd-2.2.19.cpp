static APR_INLINE void* apr_malloc_dbg(size_t size, const char* filename,
                                       int linenumber)
{
    return _malloc_dbg(size, _CRT_BLOCK, filename, linenumber);
}