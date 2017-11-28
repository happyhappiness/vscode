void Kid::stop(status_type exitStatus)
{
    assert(running());
    assert(startTime != 0);

    isRunning = false;

    time_t stop_time;
    time(&stop_time);
    if ((stop_time - startTime) < fastFailureTimeLimit)
        ++badFailures;
    else
        badFailures = 0; // the failures are not "frequent" [any more]

    status = exitStatus;
}