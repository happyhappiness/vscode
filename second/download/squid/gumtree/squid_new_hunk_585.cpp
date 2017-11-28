    ll->eol = 1;
    {
        Ip::Address localhost;
        args[0] = "(logfile-daemon)";
        args[1] = path;
        args[2] = NULL;
        localhost.setLocalhost();
        ll->pid = ipcCreate(IPC_STREAM, Log::TheConfig.logfile_daemon, args, "logfile-daemon", localhost, &ll->rfd, &ll->wfd, NULL);
        if (ll->pid < 0)
            fatal("Couldn't start logfile helper");
    }
    ll->nbufs = 0;

