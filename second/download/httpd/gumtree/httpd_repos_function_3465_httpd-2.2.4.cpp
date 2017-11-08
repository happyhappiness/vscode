static apr_uint32_t inline intel_atomic_add32(volatile apr_uint32_t *mem, 
                                              apr_uint32_t val)
{
    asm volatile ("lock; xaddl %0,%1"
                  : "=r"(val), "=m"(*mem) /* outputs */
                  : "0"(val), "m"(*mem)   /* inputs */
                  : "memory", "cc");
    return val;
}