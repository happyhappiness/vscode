void
memCheckInit(void)
{
    mem_type t = MEM_NONE;

    while (++t < MEM_MAX) {
        /*
         * If you hit this assertion, then you forgot to add a
         * memDataInit() line for type 't'.
         */
        assert(GetPool(t));
    }
}