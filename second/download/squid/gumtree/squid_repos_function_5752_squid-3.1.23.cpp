void
xprof_stop(xprof_type type, const char *timer)
{
    hrtime_t tt = get_tick();
    assert(cstack_head > 0);
    cstack_head--;
    assert(cstack[cstack_head].timer == type);

    /* Record timer details */
    cstack[cstack_head].accum += tt - cstack[cstack_head].start;
    xprof_Timers[type]->accu.delta = cstack[cstack_head].accum;
    xprof_Timers[type]->name = timer;

    /* Update */
    xprof_update(&xprof_Timers[type]->accu);

    /* Restart previous timer if we're not at the top level */
    if (cstack_head > 0) {
        cstack[cstack_head - 1].start = tt;
        cstack[cstack_head - 1].stop = 0;
        return;
    }
    /* Get here? We're at the top level; unaccounted */
    xp_UNACCOUNTED->start = tt;
}