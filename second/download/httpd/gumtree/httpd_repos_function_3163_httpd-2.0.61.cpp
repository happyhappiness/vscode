apr_int32_t apr_atomic_add(volatile apr_atomic_t *mem, apr_int32_t val) 
{
    apr_atomic_t old, new_val; 

    old = *mem;   /* old is automatically updated on cs failure */
    do {
        new_val = old + val;
    } while (__cs(&old, (cs_t *)mem, new_val)); 

    return new_val;
}