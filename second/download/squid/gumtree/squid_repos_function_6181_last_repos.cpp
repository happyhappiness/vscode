Logfile *
logfileOpen(const char *path, size_t bufsz, int fatal_flag)
{
    int ret;
    const char *patharg;

    debugs(50, DBG_IMPORTANT, "Logfile: opening log " << path);

    Logfile *lf = new Logfile(path);
    patharg = path;
    /* need to call the per-logfile-type code */
    if (strncmp(path, "stdio:", 6) == 0) {
        patharg = path + 6;
        ret = logfile_mod_stdio_open(lf, patharg, bufsz, fatal_flag);
    } else if (strncmp(path, "daemon:", 7) == 0) {
        patharg = path + 7;
        ret = logfile_mod_daemon_open(lf, patharg, bufsz, fatal_flag);
    } else if (strncmp(path, "tcp:", 4) == 0) {
        patharg = path + 4;
        ret = Log::TcpLogger::Open(lf, patharg, bufsz, fatal_flag);
    } else if (strncmp(path, "udp:", 4) == 0) {
        patharg = path + 4;
        ret = logfile_mod_udp_open(lf, patharg, bufsz, fatal_flag);
#if HAVE_SYSLOG
    } else if (strncmp(path, "syslog:", 7) == 0) {
        patharg = path + 7;
        ret = logfile_mod_syslog_open(lf, patharg, bufsz, fatal_flag);
#endif
    } else {
        debugs(50, DBG_IMPORTANT, "WARNING: log name now starts with a module name. Use 'stdio:" << patharg << "'");
        snprintf(lf->path, MAXPATHLEN, "stdio:%s", patharg);
        ret = logfile_mod_stdio_open(lf, patharg, bufsz, fatal_flag);
    }
    if (!ret) {
        if (fatal_flag)
            fatalf("logfileOpen: %s: couldn't open!\n", path);
        else
            debugs(50, DBG_IMPORTANT, "logfileOpen: " << path << ": couldn't open!");
        lf->f_close(lf);
        delete lf;
        return NULL;
    }
    assert(lf->data != NULL);

    if (fatal_flag)
        lf->flags.fatal = 1;

    lf->sequence_number = 0;

    return lf;
}