void Kid::start(pid_t cpid)
{
    assert(!running());
    assert(cpid > 0);

    isRunning = true;
    pid = cpid;
    time(&startTime);
}