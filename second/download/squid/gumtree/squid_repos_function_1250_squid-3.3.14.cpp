static int
MemPoolReportSorter(const void *a, const void *b)
{
    const MemPoolStats *A =  (MemPoolStats *) a;
    const MemPoolStats *B =  (MemPoolStats *) b;

    // use this to sort on %Total Allocated
    //
    double pa = (double) A->obj_size * A->meter->alloc.level;
    double pb = (double) B->obj_size * B->meter->alloc.level;

    if (pa > pb)
        return -1;

    if (pb > pa)
        return 1;

#if 0
    // use this to sort on In Use high(hrs)
    //
    if (A->meter->inuse.hwater_stamp > B->meter->inuse.hwater_stamp)
        return -1;

    if (B->meter->inuse.hwater_stamp > A->meter->inuse.hwater_stamp)
        return 1;

#endif

    return 0;
}