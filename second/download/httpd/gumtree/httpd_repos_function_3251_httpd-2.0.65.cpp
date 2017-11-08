inline int apr_atomic_dec(apr_atomic_t *mem) 
{
    return (atomic_xchgadd(mem, 0xFFFFFFFF) - 1);
}