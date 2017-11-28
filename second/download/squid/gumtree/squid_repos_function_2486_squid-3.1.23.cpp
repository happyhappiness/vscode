void
comm_select_init(void)
{
    kq = kqueue();

    if (kq < 0) {
        fatal("comm_select_init: Couldn't open kqueue fd!\n");
    }

    kqmax = getdtablesize();

    kqlst = (struct kevent *)xmalloc(sizeof(*kqlst) * kqmax);
    zero_timespec.tv_sec = 0;
    zero_timespec.tv_nsec = 0;

    commKQueueRegisterWithCacheManager();
}