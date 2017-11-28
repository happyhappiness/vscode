static int
SquidMainSafe(int argc, char **argv)
{
    (void)std::set_terminate(&OnTerminate);
    // XXX: This top-level catch works great for startup, but, during runtime,
    // it erases valuable stack info. TODO: Let stack-preserving OnTerminate()
    // handle FATAL runtime errors by splitting main code into protected
    // startup, unprotected runtime, and protected termination sections!
    try {
        return SquidMain(argc, argv);
    } catch (...) {
        debugs(1, DBG_CRITICAL, "FATAL: " << CurrentException);
    }
    return -1; // TODO: return EXIT_FAILURE instead
}