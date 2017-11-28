static void
RemoveInstance()
{
    if (ThePidFileToRemove.isEmpty()) // not the PidFilename()!
        return; // nothing to do

    debugs(50, DBG_IMPORTANT, "Removing " << PidFileDescription(ThePidFileToRemove));
    const char *filename = ThePidFileToRemove.c_str(); // avoid complex operations inside enter_suid()
    enter_suid();
    safeunlink(filename, 0);
    leave_suid();

    ThePidFileToRemove.clear();
}