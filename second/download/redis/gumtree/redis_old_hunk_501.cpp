        start_addr = strtoul(start,NULL,16);
        end_addr = strtoul(end,NULL,16);
        size = end_addr-start_addr;

        start_vect[regions] = start_addr;
        size_vect[regions] = size;
        printf("Testing %lx %lu\n", (unsigned long) start_vect[regions],
                                    (unsigned long) size_vect[regions]);
        regions++;
    }

    /* Test all the regions as an unique sequential region.
     * 1) Take the CRC64 of the memory region. */
    for (j = 0; j < regions; j++) {
        crc1 = crc64(crc1,(void*)start_vect[j],size_vect[j]);
    }

    /* 2) Invert bits, swap adjacent words, swap again, invert bits.
     * This is the error amplification step. */
    for (j = 0; j < regions; j++)
        memtest_non_destructive_invert((void*)start_vect[j],size_vect[j]);
    for (j = 0; j < regions; j++)
        memtest_non_destructive_swap((void*)start_vect[j],size_vect[j]);
    for (j = 0; j < regions; j++)
        memtest_non_destructive_swap((void*)start_vect[j],size_vect[j]);
    for (j = 0; j < regions; j++)
        memtest_non_destructive_invert((void*)start_vect[j],size_vect[j]);

    /* 3) Take the CRC64 sum again. */
    for (j = 0; j < regions; j++)
        crc2 = crc64(crc2,(void*)start_vect[j],size_vect[j]);

    /* 4) Swap + Swap again */
    for (j = 0; j < regions; j++)
        memtest_non_destructive_swap((void*)start_vect[j],size_vect[j]);
    for (j = 0; j < regions; j++)
        memtest_non_destructive_swap((void*)start_vect[j],size_vect[j]);

    /* 5) Take the CRC64 sum again. */
    for (j = 0; j < regions; j++)
        crc3 = crc64(crc3,(void*)start_vect[j],size_vect[j]);

    /* NOTE: It is very important to close the file descriptor only now
     * because closing it before may result into unmapping of some memory
     * region that we are testing. */
    fclose(fp);

    /* If the two CRC are not the same, we trapped a memory error. */
    return crc1 != crc2 || crc2 != crc3;
}
#endif

void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
    ucontext_t *uc = (ucontext_t*) secret;
    sds infostring, clients;
    struct sigaction act;
    REDIS_NOTUSED(info);

    bugReportStart();
    redisLog(REDIS_WARNING,
        "    Redis %s crashed by signal: %d", REDIS_VERSION, sig);
    if (sig == SIGSEGV) {
        redisLog(REDIS_WARNING,
        "    SIGSEGV caused by address: %p", (void*)info->si_addr);
    }
    redisLog(REDIS_WARNING,
        "    Failed assertion: %s (%s:%d)", server.assert_failed,
                        server.assert_file, server.assert_line);

    /* Log the stack trace */
    redisLog(REDIS_WARNING, "--- STACK TRACE");
    logStackTrace(uc);

    /* Log INFO and CLIENT LIST */
    redisLog(REDIS_WARNING, "--- INFO OUTPUT");
    infostring = genRedisInfoString("all");
    infostring = sdscatprintf(infostring, "hash_init_value: %u\n",
        dictGetHashFunctionSeed());
    redisLogRaw(REDIS_WARNING, infostring);
    redisLog(REDIS_WARNING, "--- CLIENT LIST OUTPUT");
    clients = getAllClientsInfoString();
    redisLogRaw(REDIS_WARNING, clients);
    sdsfree(infostring);
    sdsfree(clients);

    /* Log the current client */
    logCurrentClient();

    /* Log dump of processor registers */
    logRegisters(uc);

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
"  Suspect RAM error? Use redis-server --test-memory to verify it.\n\n"
);
    /* free(messages); Don't call free() with possibly corrupted memory. */
    if (server.daemonize) unlink(server.pidfile);

    /* Make sure we exit with the right signal at the end. So for instance
     * the core will be dumped if enabled. */
    sigemptyset (&act.sa_mask);
    act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND;
    act.sa_handler = SIG_DFL;
