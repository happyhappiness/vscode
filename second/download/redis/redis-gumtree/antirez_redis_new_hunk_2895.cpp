    *((char*)-1) = 'x';
#endif
}

#ifdef HAVE_BACKTRACE
static void *getMcontextEip(ucontext_t *uc) {
#if defined(__FreeBSD__)
    return (void*) uc->uc_mcontext.mc_eip;
#elif defined(__dietlibc__)
    return (void*) uc->uc_mcontext.eip;
#elif defined(__APPLE__) && !defined(MAC_OS_X_VERSION_10_6)
  #if __x86_64__
    return (void*) uc->uc_mcontext->__ss.__rip;
  #elif __i386__
    return (void*) uc->uc_mcontext->__ss.__eip;
  #else
    return (void*) uc->uc_mcontext->__ss.__srr0;
  #endif
#elif defined(__APPLE__) && defined(MAC_OS_X_VERSION_10_6)
  #if defined(_STRUCT_X86_THREAD_STATE64) && !defined(__i386__)
    return (void*) uc->uc_mcontext->__ss.__rip;
  #else
    return (void*) uc->uc_mcontext->__ss.__eip;
  #endif
#elif defined(__i386__)
    return (void*) uc->uc_mcontext.gregs[14]; /* Linux 32 */
#elif defined(__X86_64__) || defined(__x86_64__)
    return (void*) uc->uc_mcontext.gregs[16]; /* Linux 64 */
#elif defined(__ia64__) /* Linux IA64 */
    return (void*) uc->uc_mcontext.sc_ip;
#else
    return NULL;
#endif
}

void bugReportStart(void) {
    if (server.bug_report_start == 0) {
        redisLog(REDIS_WARNING,
            "\n\n=== REDIS BUG REPORT START: Cut & paste starting from here ===");
        server.bug_report_start = 1;
    }
}

void logStackContent(void **sp) {
    int i;
    for (i = 15; i >= 0; i--) {
        if (sizeof(long) == 4)
            redisLog(REDIS_WARNING, "(%08lx) -> %08lx", sp+i, sp[i]);
        else
            redisLog(REDIS_WARNING, "(%016lx) -> %016lx", sp+i, sp[i]);
    }
}

void logRegisters(ucontext_t *uc) {
    redisLog(REDIS_WARNING, "--- REGISTERS");
#if defined(__APPLE__) && defined(MAC_OS_X_VERSION_10_6)
  #if defined(_STRUCT_X86_THREAD_STATE64) && !defined(__i386__)
    redisLog(REDIS_WARNING,
    "\n"
    "RAX:%016lx RBX:%016lx\nRCX:%016lx RDX:%016lx\n"
    "RDI:%016lx RSI:%016lx\nRBP:%016lx RSP:%016lx\n"
    "R8 :%016lx R9 :%016lx\nR10:%016lx R11:%016lx\n"
    "R12:%016lx R13:%016lx\nR14:%016lx R15:%016lx\n"
    "RIP:%016lx EFL:%016lx\nCS :%016lx FS:%016lx  GS:%016lx",
        uc->uc_mcontext->__ss.__rax,
        uc->uc_mcontext->__ss.__rbx,
        uc->uc_mcontext->__ss.__rcx,
        uc->uc_mcontext->__ss.__rdx,
        uc->uc_mcontext->__ss.__rdi,
        uc->uc_mcontext->__ss.__rsi,
        uc->uc_mcontext->__ss.__rbp,
        uc->uc_mcontext->__ss.__rsp,
        uc->uc_mcontext->__ss.__r8,
        uc->uc_mcontext->__ss.__r9,
        uc->uc_mcontext->__ss.__r10,
        uc->uc_mcontext->__ss.__r11,
        uc->uc_mcontext->__ss.__r12,
        uc->uc_mcontext->__ss.__r13,
        uc->uc_mcontext->__ss.__r14,
        uc->uc_mcontext->__ss.__r15,
        uc->uc_mcontext->__ss.__rip,
        uc->uc_mcontext->__ss.__rflags,
        uc->uc_mcontext->__ss.__cs,
        uc->uc_mcontext->__ss.__fs,
        uc->uc_mcontext->__ss.__gs
    );
    logStackContent((void**)uc->uc_mcontext->__ss.__rsp);
  #else
    redisLog(REDIS_WARNING,
    "\n"
    "EAX:%08lx EBX:%08lx ECX:%08lx EDX:%08lx\n"
    "EDI:%08lx ESI:%08lx EBP:%08lx ESP:%08lx\n"
    "SS:%08lx  EFL:%08lx EIP:%08lx CS :%08lx\n"
    "DS:%08lx  ES:%08lx  FS :%08lx GS :%08lx",
        uc->uc_mcontext->__ss.__eax,
        uc->uc_mcontext->__ss.__ebx,
        uc->uc_mcontext->__ss.__ecx,
        uc->uc_mcontext->__ss.__edx,
        uc->uc_mcontext->__ss.__edi,
        uc->uc_mcontext->__ss.__esi,
        uc->uc_mcontext->__ss.__ebp,
        uc->uc_mcontext->__ss.__esp,
        uc->uc_mcontext->__ss.__ss,
        uc->uc_mcontext->__ss.__eflags,
        uc->uc_mcontext->__ss.__eip,
        uc->uc_mcontext->__ss.__cs,
        uc->uc_mcontext->__ss.__ds,
        uc->uc_mcontext->__ss.__es,
        uc->uc_mcontext->__ss.__fs,
        uc->uc_mcontext->__ss.__gs
    );
    logStackContent((void**)uc->uc_mcontext->__ss.__esp);
  #endif
#elif defined(__i386__)
    redisLog(REDIS_WARNING,
    "\n"
    "EAX:%08lx EBX:%08lx ECX:%08lx EDX:%08lx\n"
    "EDI:%08lx ESI:%08lx EBP:%08lx ESP:%08lx\n"
    "SS :%08lx EFL:%08lx EIP:%08lx CS:%08lx\n"
    "DS :%08lx ES :%08lx FS :%08lx GS:%08lx",
        uc->uc_mcontext.gregs[11],
        uc->uc_mcontext.gregs[8],
        uc->uc_mcontext.gregs[10],
        uc->uc_mcontext.gregs[9],
        uc->uc_mcontext.gregs[4],
        uc->uc_mcontext.gregs[5],
        uc->uc_mcontext.gregs[6],
        uc->uc_mcontext.gregs[7],
        uc->uc_mcontext.gregs[18],
        uc->uc_mcontext.gregs[17],
        uc->uc_mcontext.gregs[14],
        uc->uc_mcontext.gregs[15],
        uc->uc_mcontext.gregs[3],
        uc->uc_mcontext.gregs[2],
        uc->uc_mcontext.gregs[1],
        uc->uc_mcontext.gregs[0]
    );
    logStackContent((void**)uc->uc_mcontext.gregs[7]);
#elif defined(__X86_64__) || defined(__x86_64__)
    redisLog(REDIS_WARNING,
    "\n"
    "RAX:%016lx RBX:%016lx\nRCX:%016lx RDX:%016lx\n"
    "RDI:%016lx RSI:%016lx\nRBP:%016lx RSP:%016lx\n"
    "R8 :%016lx R9 :%016lx\nR10:%016lx R11:%016lx\n"
    "R12:%016lx R13:%016lx\nR14:%016lx R15:%016lx\n"
    "RIP:%016lx EFL:%016lx\nCSGSFS:%016lx",
        uc->uc_mcontext.gregs[13],
        uc->uc_mcontext.gregs[11],
        uc->uc_mcontext.gregs[14],
        uc->uc_mcontext.gregs[12],
        uc->uc_mcontext.gregs[8],
        uc->uc_mcontext.gregs[9],
        uc->uc_mcontext.gregs[10],
        uc->uc_mcontext.gregs[15],
        uc->uc_mcontext.gregs[0],
        uc->uc_mcontext.gregs[1],
        uc->uc_mcontext.gregs[2],
        uc->uc_mcontext.gregs[3],
        uc->uc_mcontext.gregs[4],
        uc->uc_mcontext.gregs[5],
        uc->uc_mcontext.gregs[6],
        uc->uc_mcontext.gregs[7],
        uc->uc_mcontext.gregs[16],
        uc->uc_mcontext.gregs[17],
        uc->uc_mcontext.gregs[18]
    );
    logStackContent((void**)uc->uc_mcontext.gregs[15]);
#else
    redisLog(REDIS_WARNING,
        "  Dumping of registers not supported for this OS/arch");
#endif
}

void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
    void *trace[100];
    char **messages = NULL;
    int i, trace_size = 0;
    ucontext_t *uc = (ucontext_t*) secret;
    sds infostring, clients;
    struct sigaction act;
    REDIS_NOTUSED(info);

    bugReportStart();
    redisLog(REDIS_WARNING,
        "    Redis %s crashed by signal: %d", REDIS_VERSION, sig);
    redisLog(REDIS_WARNING,
        "    Failed assertion: %s (%s:%d)", server.assert_failed,
                        server.assert_file, server.assert_line);

    /* Generate the stack trace */
    trace_size = backtrace(trace, 100);

    /* overwrite sigaction with caller's address */
    if (getMcontextEip(uc) != NULL) {
        trace[1] = getMcontextEip(uc);
    }
    messages = backtrace_symbols(trace, trace_size);
    redisLog(REDIS_WARNING, "--- STACK TRACE");
    for (i=1; i<trace_size; ++i)
        redisLog(REDIS_WARNING,"%s", messages[i]);

    /* Log INFO and CLIENT LIST */
    redisLog(REDIS_WARNING, "--- INFO OUTPUT");
    infostring = genRedisInfoString("all");
    infostring = sdscatprintf(infostring, "hash_init_value: %u\n",
        dictGetHashFunctionSeed());
    redisLogRaw(REDIS_WARNING, infostring);
    redisLog(REDIS_WARNING, "--- CLIENT LIST OUTPUT");
    clients = getAllClientsInfoString();
    redisLogRaw(REDIS_WARNING, clients);
    /* Don't sdsfree() strings to avoid a crash. Memory may be corrupted. */

    /* Log CURRENT CLIENT info */
    if (server.current_client) {
        redisClient *cc = server.current_client;
        sds client;
        int j;

        redisLog(REDIS_WARNING, "--- CURRENT CLIENT INFO");
        client = getClientInfoString(cc);
        redisLog(REDIS_WARNING,"client: %s", client);
        /* Missing sdsfree(client) to avoid crash if memory is corrupted. */
        for (j = 0; j < cc->argc; j++) {
            robj *decoded;

            decoded = getDecodedObject(cc->argv[j]);
            redisLog(REDIS_WARNING,"argv[%d]: '%s'", j, (char*)decoded->ptr);
            decrRefCount(decoded);
        }
        /* Check if the first argument, usually a key, is found inside the
         * selected DB, and if so print info about the associated object. */
        if (cc->argc >= 1) {
            robj *val, *key;
            dictEntry *de;

            key = getDecodedObject(cc->argv[1]);
            de = dictFind(cc->db->dict, key->ptr);
            if (de) {
                val = dictGetVal(de);
                redisLog(REDIS_WARNING,"key '%s' found in DB containing the following object:", key->ptr);
                redisLogObjectDebugInfo(val);
            }
            decrRefCount(key);
        }
    }

    /* Log dump of processor registers */
    logRegisters(uc);

    redisLog(REDIS_WARNING,
"\n=== REDIS BUG REPORT END. Make sure to include from START to END. ===\n\n"
"    Please report the crash opening an issue on github:\n\n"
"        http://github.com/antirez/redis/issues\n\n"
);
    /* free(messages); Don't call free() with possibly corrupted memory. */
    if (server.daemonize) unlink(server.pidfile);

    /* Make sure we exit with the right signal at the end. So for instance
     * the core will be dumped if enabled. */
    sigemptyset (&act.sa_mask);
    /* When the SA_SIGINFO flag is set in sa_flags then sa_sigaction
     * is used. Otherwise, sa_handler is used */
    act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND;
    act.sa_handler = SIG_DFL;
    sigaction (sig, &act, NULL);
    kill(getpid(),sig);
}
#endif /* HAVE_BACKTRACE */
