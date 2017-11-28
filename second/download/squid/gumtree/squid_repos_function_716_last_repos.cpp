static
int
parseConfigFileOrThrow(const char *file_name)
{
    int err_count = 0;

    debugs(5, 4, HERE);

    configFreeMemory();

    ACLMethodData::ThePurgeCount = 0;
    default_all();

    err_count = parseOneConfigFile(file_name, 0);

    defaults_if_none();

    defaults_postscriptum();

    /*
     * We must call configDoConfigure() before leave_suid() because
     * configDoConfigure() is where we turn username strings into
     * uid values.
     */
    configDoConfigure();

    if (!Config.chroot_dir) {
        leave_suid();
        setUmask(Config.umask);
        _db_init(Debug::cache_log, Debug::debugOptions);
        enter_suid();
    }

    if (opt_send_signal == -1) {
        Mgr::RegisterAction("config",
                            "Current Squid Configuration",
                            dump_config,
                            1, 1);
    }

    return err_count;
}