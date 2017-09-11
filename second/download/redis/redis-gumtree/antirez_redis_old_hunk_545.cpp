
#if defined(HAVE_PROC_MAPS)
    /* Test memory */
    serverLog(LL_WARNING, "--- FAST MEMORY TEST");
    bioKillThreads();
    if (memtest_test_linux_anonymous_maps()) {
        serverLog(LL_WARNING,
