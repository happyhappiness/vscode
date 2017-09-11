    REDIS_NOTUSED(info);
    REDIS_NOTUSED(sig);
    sds st, log;
    time_t now = time(NULL);
    char date[128];
    FILE *fp;

    fp = (server.logfile == NULL) ? stdout : fopen(server.logfile,"a");
    if (fp == NULL) return;

    strftime(date,sizeof(date),"%d %b %H:%M:%S",localtime(&now));
    log = sdscatprintf(sdsempty(),
        "\n--- WATCHDOG TIMER EXPIRED (%s) ---\n",date); 
#ifdef HAVE_BACKTRACE
    st = getStackTrace(uc);
#else
    st = sdsnew("Sorry: no support for backtrace().\n");
#endif
    log = sdscatsds(log,st);
    log = sdscat(log,"------\n\n");
    fprintf(fp,"%s",log);
    if (server.logfile) fclose(fp);
    sdsfree(st);
    sdsfree(log);
}
