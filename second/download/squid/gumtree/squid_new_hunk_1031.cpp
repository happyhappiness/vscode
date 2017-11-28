void
Comm::SelectLoopInit(void)
{
    pevents = (struct epoll_event *) xmalloc(SQUID_MAXFD * sizeof(struct epoll_event));

    if (!pevents) {
        int xerrno = errno;
        fatalf("comm_select_init: xmalloc() failed: %s\n", xstrerr(xerrno));
    }

    kdpfd = epoll_create(SQUID_MAXFD);

    if (kdpfd < 0) {
        int xerrno = errno;
        fatalf("comm_select_init: epoll_create(): %s\n", xstrerr(xerrno));
    }

    commEPollRegisterWithCacheManager();
}

static const char* epolltype_atoi(int x)
