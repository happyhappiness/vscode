static SBuf
PidFilenameCalc()
{
    if (!Config.pidFilename || strcmp(Config.pidFilename, "none") == 0)
        return SBuf();

    // If chroot has been requested, then we first read the PID file before
    // chroot() and then create/update it inside a chrooted environment.
    // TODO: Consider removing half-baked chroot support from Squid.
    extern bool Chrooted;
    if (!Config.chroot_dir || Chrooted) // no need to compensate
        return SBuf(Config.pidFilename);

    SBuf filename;
    filename.append(Config.chroot_dir);
    filename.append("/");
    filename.append(Config.pidFilename);
    debugs(50, 3, "outside chroot: " << filename);
    return filename;
}