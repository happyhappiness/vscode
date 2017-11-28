bool
IamWorkerProcess()
{
    // when there is only one process, it has to be the worker
    if (opt_no_daemon || Config.workers == 0)
        return true;

    return TheProcessKind == pkWorker;
}