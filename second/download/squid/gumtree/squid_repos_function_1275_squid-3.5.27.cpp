void
memCheckInit(void)
{
    mem_type t = MEM_NONE;

    while (++t < MEM_DONTFREE) {
        /*
         * If you hit this assertion, then you forgot to add a
         * memDataInit() line for type 't'.
         * Or placed the pool type in the wrong section of the enum list.
         */
        assert(MemPools[t]);
    }
}