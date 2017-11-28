        }

        sendSignal();
        /* NOTREACHED */
    }

    if (opt_create_swap_dirs) {
        /* chroot if configured to run inside chroot */

        if (Config.chroot_dir && chroot(Config.chroot_dir)) {
            fatal("failed to chroot");
        }

        setEffectiveUser();
        debugs(0, 0, "Creating Swap Directories");
        Store::Root().create();

        return 0;
    }

    if (!opt_no_daemon)
        watch_child(argv);

    setMaxFD();

    /* init comm module */
    comm_init();

    comm_select_init();

    if (opt_no_daemon) {
        /* we have to init fdstat here. */
        fd_open(0, FD_LOG, "stdin");
        fd_open(1, FD_LOG, "stdout");
        fd_open(2, FD_LOG, "stderr");
    }
