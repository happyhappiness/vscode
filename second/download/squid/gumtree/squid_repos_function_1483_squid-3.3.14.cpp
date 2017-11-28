static int
SquidMainSafe(int argc, char **argv)
{
    try {
        return SquidMain(argc, argv);
    } catch (const std::exception &e) {
        debugs(1, DBG_CRITICAL, "FATAL: dying from an unhandled exception: " <<
               e.what());
        throw;
    } catch (...) {
        debugs(1, DBG_CRITICAL, "FATAL: dying from an unhandled exception.");
        throw;
    }
    return -1; // not reached
}