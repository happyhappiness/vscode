    /* Step 2: rewrite every single option, replacing or appending it inside
     * the rewrite state. */

    /* TODO: Turn every default into a define, use it also in
     * initServerConfig(). */
    rewriteConfigYesNoOption(state,"daemonize",server.daemonize,0);
    rewriteConfigStringOption(state,"pidfile",server.pidfile,REDIS_DEFAULT_PID_FILE);
    rewriteConfigNumericalOption(state,"port",server.port,REDIS_SERVERPORT);
