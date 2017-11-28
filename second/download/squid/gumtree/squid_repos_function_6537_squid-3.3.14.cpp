void
Mgr::RotateAction::dump(StoreEntry* entry)
{
    debugs(16, DBG_IMPORTANT, "Rotate Logs by Cache Manager command.");
    storeAppendPrintf(entry, "Rotating Squid Process Logs ....");
#if defined(_SQUID_LINUX_THREADS_)
    rotate_logs(SIGQUIT);
#else
    rotate_logs(SIGUSR1);
#endif
}