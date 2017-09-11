        return 0;
    }
}

/* This is the timer handler we use to incrementally perform collection
 * into the lazy free lists. We can't use serverCron since we need a
 * very high timer frequency when there are many objects to collect, while
 * we lower the frequency to just 1HZ when there is nothing to do.
 *
 * Since a slow lazy free step will take 1.5 milliseconds and we modulate
 * the timer frequency from 1 to 333 HZ in an adaptive way, the CPU
 * used is between 0% (nothing in the lazy free list) to 50%.
 *
 * The frequency is obtained as follows: if the lazy free list is empty
 * it is set to 1HZ. If the lazy free has elements the call period starts
 * at 20 (50HZ) and is decremented (up to 3 ms = 333HZ) each time the server
 * used memory raises between calls of this function. */
int lazyfreeCron(struct aeEventLoop *eventLoop, long long id, void *clientData)
{
    UNUSED(eventLoop);
    UNUSED(id);
    UNUSED(clientData);

    /* Threaded lazy free does not need a timer, unregister the timer event. */
    if (lazyfree_threaded) return AE_NOMORE;

    static size_t prev_mem;
    static int timer_period = 1000; /* Defauls to 1HZ */
    static double mem_trend = 0;
    size_t mem = zmalloc_used_memory();

    /* Compute the memory trend, biased towards thinking memory is raising
     * for a few calls every time previous and current memory raise. */
    if (prev_mem < mem) mem_trend = 1;
    mem_trend *= 0.9; /* Make it slowly forget. */
    int mem_is_raising = mem_trend > .1;

    /* Free a few items. */
    size_t workdone = lazyfreeStep(LAZYFREE_STEP_SLOW);

    /* Adjust this timer call frequency according to the current state. */
    if (workdone) {
        if (timer_period == 1000) timer_period = 20;
        if (mem_is_raising && timer_period > 3)
            timer_period--; /* Raise call frequency. */
        else if (!mem_is_raising && timer_period < 20)
            timer_period++; /* Lower call frequency. */
    } else {
        timer_period = 1000;    /* 1 HZ */
    }
    prev_mem = mem;
#if 0
    printf("%llu (%d hz) %s (%f)\n",
        (unsigned long long)server.lazyfree_elements,
        1000/timer_period,
        mem_is_raising ? "RAISING" : "lowering",
        mem_trend);
#endif
    return timer_period;
}
