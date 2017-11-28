void
MemObject::delayRead(DeferredRead const &aRead)
{
#if USE_DELAY_POOLS
    if (readAheadPolicyCanRead()) {
        if (DelayId mostAllowedId = mostBytesAllowed()) {
            mostAllowedId.delayRead(aRead);
            return;
        }
    }
#endif
    deferredReads.delayRead(aRead);
}