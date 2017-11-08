int apr_atomic_dec32(volatile apr_uint32_t *mem)
{
    apr_uint32_t old_value, new_value;
    
    do {
        old_value = *mem;
        new_value = old_value - 1;
    } while (apr_atomic_cas32(mem, new_value, old_value) != old_value);
    return old_value != 1;
}