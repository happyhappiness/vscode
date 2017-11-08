static APR_INLINE void* apr_realloc_dbg(void* userData, size_t newSize,
                                        const char* filename, int linenumber)
{
    return _realloc_dbg(userData, newSize, _CRT_BLOCK, filename, linenumber);
}