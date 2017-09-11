    bugReportStart();
    serverLog(LL_WARNING,
        "    Redis %s crashed by signal: %d", REDIS_VERSION, sig);
    serverLog(LL_WARNING,
        "    Failed assertion: %s (%s:%d)", server.assert_failed,
                        server.assert_file, server.assert_line);
