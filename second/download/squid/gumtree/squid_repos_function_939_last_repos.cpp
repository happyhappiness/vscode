static void
ThrowIfAlreadyRunningWith(File &pidFile)
{
    bool running = false;
    SBuf description;
    try {
        const auto pid = GetOtherPid(pidFile);
        description = ToSBuf(TheFile, " with PID ", pid);
        running = ProcessIsRunning(pid);
    }
    catch (const std::exception &ex) {
        debugs(50, 5, "assuming no other Squid instance: " << ex.what());
        return;
    }

    if (running)
        throw TexcHere(ToSBuf("Squid is already running: Found fresh instance ", description));

    debugs(50, 5, "assuming stale instance " << description);
}