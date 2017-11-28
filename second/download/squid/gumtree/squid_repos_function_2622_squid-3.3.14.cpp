bool
IamPrimaryProcess()
{
    // when there is only one process, it has to be primary
    if (opt_no_daemon || Config.workers == 0)
        return true;

    // when there is a master and worker process, the master delegates
    // primary functions to its only kid
    if (NumberOfKids() == 1)
        return IamWorkerProcess();

    // in SMP mode, multiple kids delegate primary functions to the coordinator
    return IamCoordinatorProcess();
}