apr_uint32_t apr_atomic_xchg32(volatile apr_uint32_t *mem, apr_uint32_t val)
{
    apr_uint32_t prev;
    do {
        prev = *mem;
    } while (apr_atomic_cas32(mem, val, prev) != prev);
    return prev;
}