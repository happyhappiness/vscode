}

void logRegisters(ucontext_t *uc) {
    serverLog(LL_WARNING|LL_RAW, "\n------ REGISTERS ------\n");

/* OSX */
#if defined(__APPLE__) && defined(MAC_OS_X_VERSION_10_6)
