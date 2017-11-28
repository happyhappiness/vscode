void
memCheckInit(void)
{
    mem_type t;

    for (t = MEM_NONE, ++t; t < MEM_MAX; ++t) {
        if (MEM_DONTFREE == t)
            continue;

        /*
         * If you hit this assertion, then you forgot to add a
         * memDataInit() line for type 't'.
         */
        assert(MemPools[t]);
    }
}