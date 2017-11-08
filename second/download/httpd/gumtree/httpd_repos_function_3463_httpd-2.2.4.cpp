apr_uint32_t apr_atomic_cas32(volatile apr_uint32_t *mem, apr_uint32_t swap, 
                              apr_uint32_t cmp)
{
    apr_uint32_t old = cmp;
    
    __cs(&old, (cs_t *)mem, swap);
    return old; /* old is automatically updated from mem on cs failure */
}