            fprintf(stderr, "StartServiceCtrlDispatcher error = %ld\n",
                    GetLastError());
            return 1;
        }
    } else {
        WIN32_run_mode = _WIN_SQUID_RUN_MODE_INTERACTIVE;
#if _SQUID_MSWIN_

        opt_no_daemon = 1;

#endif

        return SquidMain(argc, argv);
