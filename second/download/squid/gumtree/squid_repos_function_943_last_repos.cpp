void
Instance::WriteOurPid()
{
    // Instance code assumes that we do not support PID filename reconfiguration
    static bool called = false;
    Must(!called);
    called = true;

    const auto filename = PidFilename();
    if (filename.isEmpty())
        return; // nothing to do

    File pidFile(filename, File::Be::ReadWrite().locked().createdIfMissing().openedByRoot());

    // another instance may have started after the caller checked (if it did)
    ThrowIfAlreadyRunningWith(pidFile);

    /* now we know that we own the PID file created and/or locked above */

    // Cleanup is scheduled through atexit() to ensure both:
    // - cleanup upon fatal() and similar "unplanned" exits and
    // - enter_suid() existence and proper logging support during cleanup.
    // Even without PID filename reconfiguration support, we have to remember
    // the file name we have used because Config.pidFilename may change!
    (void)std::atexit(&RemoveInstance); // failures leave the PID file on disk
    ThePidFileToRemove = filename;

    /* write our PID to the locked file */
    SBuf pidBuf;
    pidBuf.Printf("%d\n", static_cast<int>(getpid()));
    pidFile.truncate();
    pidFile.writeAll(pidBuf);

    // We must fsync before releasing the lock or other Squid processes may not see
    // our written PID (and decide that they are dealing with a corrupted PID file).
    pidFile.synchronize();

    debugs(50, DBG_IMPORTANT, "Created " << TheFile);
}