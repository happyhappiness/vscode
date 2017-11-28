static int
MemPoolReportSorter(const void *a, const void *b)
{
    const MemPoolStats *A =  (MemPoolStats *) a;
    const MemPoolStats *B =  (MemPoolStats *) b;

    // use this to sort on %Total Allocated
    //
    double pa = (double) A->obj_size * A->meter->alloc.currentLevel();
    double pb = (double) B->obj_size * B->meter->alloc.currentLevel();

    if (pa > pb)
        return -1;

    if (pb > pa)
        return 1;

#if 0
    // use this to sort on In Use high(hrs)
    //
    if (A->meter->inuse.peakTime() > B->meter->inuse.peakTime())
        return -1;

    if (B->meter->inuse.peakTime() > A->meter->inuse.peakTime())
        return 1;

#endif

    return 0;
}