        if (Config.adminEmail)
            mail_warranty();

        puts(dead_msg());
    }

    abort();
}

void
BroadcastSignalIfAny(int& sig)
{
    if (sig > 0) {
        if (IamCoordinatorProcess())
            Ipc::Coordinator::Instance()->broadcastSignal(sig);
        sig = -1;
    }
}

void
sigusr2_handle(int sig)
{
    static int state = 0;
    /* no debugs() here; bad things happen if the signal is delivered during _db_print() */

    DebugSignal = sig;

    if (state == 0) {
#if !MEM_GEN_TRACE
        Debug::parseOptions("ALL,7");
#else

        log_trace_done();
#endif

        state = 1;
    } else {
#if !MEM_GEN_TRACE
        Debug::parseOptions(Debug::debugOptions);
#else

        log_trace_init("/tmp/squid.alloc");
#endif

