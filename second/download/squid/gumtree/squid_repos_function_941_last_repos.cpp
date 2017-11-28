void
Instance::ThrowIfAlreadyRunning()
{
    const auto filename = PidFilename();
    if (filename.isEmpty())
        return; // the check is impossible

    if (const auto filePtr = File::Optional(filename, File::Be::ReadOnly().locked())) {
        const std::unique_ptr<File> pidFile(filePtr);
        ThrowIfAlreadyRunningWith(*pidFile);
    } else {
        // It is best to assume then to check because checking without a lock
        // might lead to false positives that lead to no Squid starting at all!
        debugs(50, 5, "cannot lock " << TheFile << "; assuming no other Squid is running");
        // If our assumption is false, we will fail to _create_ the PID file,
        // and, hence, will not start, allowing that other Squid to run.
    }
}