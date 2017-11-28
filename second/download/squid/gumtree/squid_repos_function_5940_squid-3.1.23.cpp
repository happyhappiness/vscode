static inline hrtime_t
get_tick(void)
{
    uint32_t lo, hi;
    // Based on an example in Wikipedia
    /* We cannot use "=A", since this would use %rax on x86_64 */
asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));
    return (hrtime_t)hi << 32 | lo;
}