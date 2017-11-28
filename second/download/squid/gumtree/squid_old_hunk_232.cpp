
    /* use the standard time service */
    TimeEngine time_engine;

    mainLoop.setTimeService(&time_engine);

    mainLoop.run();

    if (mainLoop.errcount == 10)
        fatal_dump("Event loop exited with failure.");

    /* shutdown squid now */
