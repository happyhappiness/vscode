void
squidaio_stats(StoreEntry * sentry)
{
    squidaio_thread_t *threadp;
    int i;

    if (!squidaio_initialised)
        return;

    storeAppendPrintf(sentry, "\n\nThreads Status:\n");

    storeAppendPrintf(sentry, "#\tID\t# Requests\n");

    threadp = threads;

    for (i = 0; i < NUMTHREADS; ++i) {
        storeAppendPrintf(sentry, "%i\t0x%lx\t%ld\n", i + 1, (unsigned long)threadp->thread, threadp->requests);
        threadp = threadp->next;
    }
}