     /* Step 1: read the old config into our rewrite state. */
     if ((state = rewriteConfigReadOldFile(path)) == NULL) return -1;
 
     /* Step 2: rewrite every single option, replacing or appending it inside
      * the rewrite state. */
 
-    /* TODO: Turn every default into a define, use it also in
-     * initServerConfig(). */
     rewriteConfigYesNoOption(state,"daemonize",server.daemonize,0);
     rewriteConfigStringOption(state,"pidfile",server.pidfile,REDIS_DEFAULT_PID_FILE);
     rewriteConfigNumericalOption(state,"port",server.port,REDIS_SERVERPORT);
     rewriteConfigBindOption(state);
     rewriteConfigStringOption(state,"unixsocket",server.unixsocket,NULL);
     rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,REDIS_DEFAULT_UNIX_SOCKET_PERM);
