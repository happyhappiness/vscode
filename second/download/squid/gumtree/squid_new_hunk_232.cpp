
    /* use the standard time service */
    TimeEngine time_engine;

    mainLoop.setTimeService(&time_engine);

    if (IamCoordinatorProcess())
        AsyncJob::Start(Ipc::Coordinator::Instance());
    else if (UsingSmp() && (IamWorkerProcess() || IamDiskProcess()))
        AsyncJob::Start(new Ipc::Strand);

    /* at this point we are finished the synchronous startup. */
    starting_up = 0;

    mainLoop.run();

    if (mainLoop.errcount == 10)
        fatal_dump("Event loop exited with failure.");

    /* shutdown squid now */
