apr_uint32_t apr_atomic_add32(volatile apr_uint32_t *mem, apr_uint32_t val)
{
    apr_uint32_t old_value, new_value;
    
    do {
        old_value = *mem;
        new_value = old_value + val;
    } while (apr_atomic_cas32(mem, new_value, old_value) != old_value);
    return old_value;
}