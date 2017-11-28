static __inline hrtime_t
get_tick(void)
{
    hrtime_t regs;

    __asm {
        cpuid
        rdtsc
        mov eax,DWORD PTR regs[0]
        mov edx,DWORD PTR regs[4]
    }
    return regs;
}