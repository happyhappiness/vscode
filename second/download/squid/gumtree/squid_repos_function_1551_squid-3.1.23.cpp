bool
EventLoop::runOnce()
{
    bool sawActivity = false;
    runOnceResult = true;
    error = false;
    loop_delay = EVENT_LOOP_TIMEOUT;

    AsyncEngine *waitingEngine = primaryEngine;
    if (!waitingEngine && !engines.empty())
        waitingEngine = engines.back();

    do {
        // generate calls and events
        typedef engine_vector::iterator EVI;
        for (EVI i = engines.begin(); i != engines.end(); ++i) {
            if (*i != waitingEngine)
                checkEngine(*i, false);
        }

        // dispatch calls accumulated so far
        sawActivity = dispatchCalls();
        if (sawActivity)
            runOnceResult = false;
    } while (sawActivity);

    if (waitingEngine != NULL)
        checkEngine(waitingEngine, true);

    if (timeService != NULL)
        timeService->tick();

    // dispatch calls scheduled by waitingEngine and timeService
    sawActivity = dispatchCalls();
    if (sawActivity)
        runOnceResult = false;

    if (error) {
        ++errcount;
        debugs(1, 0, "Select loop Error. Retry " << errcount);
    } else
        errcount = 0;

    if (errcount == 10)
        return true;

    if (last_loop)
        return true;

    return runOnceResult;
}