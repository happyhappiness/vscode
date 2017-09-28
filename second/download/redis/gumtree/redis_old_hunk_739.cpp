    vsnprintf(msg+len,sizeof(msg)-len,reason,ap);
    va_end(ap);

    if (!rdbCheckMode) {
        serverLog(LL_WARNING, "%s", msg);
        char *argv[2] = {"",server.rdb_filename};
        redis_check_rdb_main(2,argv);
    } else {
        rdbCheckError("%s",msg);
    }
    exit(1);
}

