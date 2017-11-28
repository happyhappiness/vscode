static int
SquidMainSafe(int argc, char **argv)
{
    try {
        return SquidMain(argc, argv);
    } catch (const std::exception &e) {
        std::cerr << "dying from an unhandled exception: " << e.what() << std::endl;
        debugs(1, DBG_CRITICAL, "FATAL: dying from an unhandled exception: " << e.what());
        throw;
    } catch (...) {
        std::cerr << "dying from an unhandled exception." << std::endl;
        debugs(1, DBG_CRITICAL, "FATAL: dying from an unhandled exception.");
        throw;
    }
    return -1; // not reached
}