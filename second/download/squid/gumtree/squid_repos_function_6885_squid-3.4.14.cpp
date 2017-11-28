static inline hrtime_t
get_tick(void)
{
    hrtime_t regs;

asm volatile ("rpcc %0" : "=r" (regs));
    return regs;
}