    /* Non blocking connection timeout? */
    if (server.masterhost &&
        (server.repl_state == REPL_STATE_CONNECTING ||
         server.repl_state == REPL_STATE_RECEIVE_PONG) &&
        (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
    {
        serverLog(LL_WARNING,"Timeout connecting to the MASTER...");
        undoConnectWithMaster();
