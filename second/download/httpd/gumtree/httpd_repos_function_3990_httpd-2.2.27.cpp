apr_uint32_t apr_atomic_read32(volatile apr_uint32_t *mem)
{
    return *mem;
}