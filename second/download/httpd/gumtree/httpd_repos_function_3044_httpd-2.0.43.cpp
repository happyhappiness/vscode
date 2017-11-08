int apr_atomic_dec(apr_atomic_t *mem) 
{
    atomic_dec(mem);
    return *mem; 
}