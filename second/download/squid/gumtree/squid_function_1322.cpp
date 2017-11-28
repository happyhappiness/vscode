void
Comm::SelectLoopInit(void)
{
    pevents = (struct epoll_event *) xmalloc(SQUID_MAXFD * sizeof(struct epoll_event));

    if (!pevents) {
        fatalf("comm_select_init: xmalloc() failed: %s\n",xstrerror());
    }

    kdpfd = epoll_create(SQUID_MAXFD);

    if (kdpfd < 0) {
        fatalf("comm_select_init: epoll_create(): %s\n",xstrerror());
    }

    commEPollRegisterWithCacheManager();
}