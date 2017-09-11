
#if defined(HAVE_PROC_MAPS)
    /* Test memory */
    redisLog(REDIS_WARNING, "--- FAST MEMORY TEST");
    bioKillThreads();
    if (memtest_test_linux_anonymous_maps()) {
        redisLog(REDIS_WARNING,
            "!!! MEMORY ERROR DETECTED! Check your memory ASAP !!!");
    } else {
        redisLog(REDIS_WARNING,
            "Fast memory test PASSED, however your memory can still be broken. Please run a memory test for several hours if possible.");
    }
#endif

    redisLog(REDIS_WARNING,
"\n=== REDIS BUG REPORT END. Make sure to include from START to END. ===\n\n"
"       Please report the crash by opening an issue on github:\n\n"
"           http://github.com/antirez/redis/issues\n\n"
