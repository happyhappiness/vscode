int
MemObject::mostBytesWanted(int max, bool ignoreDelayPools) const
{
#if DELAY_POOLS
    if (!ignoreDelayPools) {
        /* identify delay id with largest allowance */
        DelayId largestAllowance = mostBytesAllowed ();
        return largestAllowance.bytesWanted(0, max);
    }
#endif

    return max;
}