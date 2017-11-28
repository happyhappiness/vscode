static inline hrtime_t
get_tick(void)
{
    hrtime_t regs;

asm volatile ("rdtsc":"=A" (regs));
    return regs;
    /* We need return value, we rely on CC to optimise out needless subf calls */
    /* Note that "rdtsc" is relatively slow OP and stalls the CPU pipes, so use it wisely */
}