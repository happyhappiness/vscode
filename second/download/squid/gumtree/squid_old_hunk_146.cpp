    storeAppendPrintf(sentry, "\n\nThreads Status:\n");

    storeAppendPrintf(sentry, "#\tID\t# Requests\n");

    threadp = threads;

    for (i = 0; i < NUMTHREADS; i++) {
        storeAppendPrintf(sentry, "%i\t0x%lx\t%ld\n", i + 1, threadp->dwThreadId, threadp->requests);
        threadp = threadp->next;
    }
}
