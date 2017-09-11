    logStackContent((void**)uc->uc_mcontext.gregs[15]);
    #endif
#else
    redisLog(REDIS_WARNING,
        "  Dumping of registers not supported for this OS/arch");
#endif
}
