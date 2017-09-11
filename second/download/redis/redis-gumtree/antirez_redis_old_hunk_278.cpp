    /* free(messages); Don't call free() with possibly corrupted memory. */
    if (server.daemonize && server.supervised == 0) unlink(server.pidfile);

    /* Make sure we exit with the right signal at the end. So for instance
     * the core will be dumped if enabled. */
    sigemptyset (&act.sa_mask);
