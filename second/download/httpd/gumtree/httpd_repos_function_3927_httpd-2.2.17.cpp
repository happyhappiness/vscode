apr_uint32_t apr_atomic_xchg32(volatile apr_uint32_t *mem, apr_uint32_t val)
{
    apr_uint32_t old, new_val; 

    old = *mem;   /* old is automatically updated on cs failure */
    do {
        new_val = val;
    } while (__cs(&old, (cs_t *)mem, new_val)); 

    return old;
}