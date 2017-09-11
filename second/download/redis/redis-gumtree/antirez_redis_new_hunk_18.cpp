    if (!rdbCheckMode) {
        serverLog(LL_WARNING, "%s", msg);
        char *argv[2] = {"",server.rdb_filename};
        redis_check_rdb_main(2,argv,NULL);
    } else {
        rdbCheckError("%s",msg);
    }
