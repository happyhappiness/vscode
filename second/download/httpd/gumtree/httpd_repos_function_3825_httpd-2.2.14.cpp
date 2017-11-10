int apr_atomic_dec32(volatile apr_uint32_t *mem)
{
    apr_uint32_t old, new_val; 

    old = *mem;   /* old is automatically updated on cs failure */
    do {
        new_val = old - 1;
    } while (__cs(&old, (cs_t *)mem, new_val)); 

    return new_val != 0;
}