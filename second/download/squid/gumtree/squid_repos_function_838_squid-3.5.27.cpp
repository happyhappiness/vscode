void
DelayVector::update(int incr)
{
    /*
     * Each pool updates itself,
     * but we may have deferred reads waiting on the pool as a whole.
     */

    kickReads();
}