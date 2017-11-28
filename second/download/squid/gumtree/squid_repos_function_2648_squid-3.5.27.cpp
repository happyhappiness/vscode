void
writePidFile(void)
{
    int fd;
    const char *f = NULL;
    mode_t old_umask;
    char buf[32];

    if (!IamPrimaryProcess())
        return;

    if ((f = Config.pidFilename) == NULL)
        return;

    if (!strcmp(Config.pidFilename, "none"))
        return;

    enter_suid();

    old_umask = umask(022);

    fd = file_open(f, O_WRONLY | O_CREAT | O_TRUNC | O_TEXT);

    umask(old_umask);

    leave_suid();

    if (fd < 0) {
        debugs(50, DBG_CRITICAL, "" << f << ": " << xstrerror());
        debug_trap("Could not write pid file");
        return;
    }

    snprintf(buf, 32, "%d\n", (int) getpid());
    FD_WRITE_METHOD(fd, buf, strlen(buf));
    file_close(fd);
}