void
xprof_start(xprof_type type, const char *timer)
{
    hrtime_t tt = get_tick();
    if (!xprof_inited)
        xprof_InitLib();

    /* If nested, stop current stack frame */
    if (cstack_head > 0) {
        cstack[cstack_head - 1].accum += get_tick() - cstack[cstack_head - 1].start;
        cstack[cstack_head - 1].start = -1;
    }

    /* Are we at the first level? If so; stop the unaccounted timer */
    if (cstack_head == 0) {
        assert(xp_UNACCOUNTED->start != -1);
        xp_UNACCOUNTED->delta = tt - xp_UNACCOUNTED->start;
        xp_UNACCOUNTED->start = -1;
        xprof_update(xp_UNACCOUNTED);
    }

    /* Allocate new stack frame */
    cstack[cstack_head].start = tt;
    cstack[cstack_head].stop = -1;
    cstack[cstack_head].accum = 0;
    cstack[cstack_head].timer = type;
    cstack[cstack_head].name = timer;
    ++cstack_head;
    assert(cstack_head < MAXSTACKDEPTH);

}