void
Ipc::Mem::RegisteredRunner::useConfig()
{
    // If Squid is built with real segments, we create() real segments
    // in the master process only.  Otherwise, we create() fake
    // segments in each worker process.  We assume that only workers
    // need and can work with fake segments.
#if HAVE_SHM
    if (IamMasterProcess())
#else
    if (IamWorkerProcess())
#endif
        create();

    // we assume that master process does not need shared segments
    // unless it is also a worker
    if (!InDaemonMode() || !IamMasterProcess())
        open();
}