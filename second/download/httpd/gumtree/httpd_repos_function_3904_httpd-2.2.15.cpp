static APR_INLINE apr_uint32_t atomic_sub(volatile apr_uint32_t *mem, apr_uint32_t val)
{
    apr_uint32_t prev = *mem, temp;

    asm volatile ("loop_%=:\n"
                  "	lr  %1,%0\n"
                  "	slr %1,%3\n"
                  "	cs  %0,%1,%2\n"
                  "	jl  loop_%=\n"
                  : "+d" (prev), "+d" (temp), "=Q" (*mem)
                  : "d" (val), "m" (*mem)
                  : "cc", "memory");

    return temp;
}