
    if (!opt_no_daemon && Config.workers > 0)
        watch_child(argv);

    if (opt_create_swap_dirs) {
        /* chroot if configured to run inside chroot */
        mainSetCwd();

        setEffectiveUser();
        debugs(0, DBG_CRITICAL, "Creating missing swap directories");
        Store::Root().create();

        return 0;
