bool
DiskThreadsIOStrategy::shedLoad()
{
    /*
     * we should detect some 'too many files open' condition and return
     * NULL here.
     */
#ifdef MAGIC2

    if (aioQueueSize() > MAGIC2)
        return true;

#endif

    return false;
}