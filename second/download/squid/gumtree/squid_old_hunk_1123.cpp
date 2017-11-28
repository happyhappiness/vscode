    isRunning = true;
    pid = cpid;
    time(&startTime);
}

/// called when kid terminates, sets exiting status
void Kid::stop(status_type theExitStatus)
{
    assert(running());
    assert(startTime != 0);

    isRunning = false;

