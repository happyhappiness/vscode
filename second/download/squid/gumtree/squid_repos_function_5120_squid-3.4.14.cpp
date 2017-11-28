void
Comm::IoCallback::reset()
{
    conn = NULL;
    if (freefunc) {
        freefunc(buf);
        buf = NULL;
        freefunc = NULL;
    }
    xerrno = 0;

#if USE_DELAY_POOLS
    quotaQueueReserv = 0;
#endif
}