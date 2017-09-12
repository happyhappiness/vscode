void redisLogRaw(int level, const char *msg) {
    const int syslogLevelMap[] = { LOG_DEBUG, LOG_INFO, LOG_NOTICE, LOG_WARNING };
    const char *c = ".-*#";
    FILE *fp;
    char buf[64];
    int rawmode = (level & REDIS_LOG_RAW);

    level &= 0xff; /* clear flags */
    if (level < server.verbosity) return;

    fp = (server.logfile == NULL) ? stdout : fopen(server.logfile,"a");
    if (!fp) return;

    if (rawmode) {
        fprintf(fp,"%s",msg);
    } else {
        int off;
        struct timeval tv;

        gettimeofday(&tv,NULL);
        off = strftime(buf,sizeof(buf),"%d %b %H:%M:%S.",localtime(&tv.tv_sec));
        snprintf(buf+off,sizeof(buf)-off,"%03d",(int)tv.tv_usec/1000);
        fprintf(fp,"[%d] %s %c %s\n",(int)getpid(),buf,c[level],msg);
    }
    fflush(fp);

    if (server.logfile) fclose(fp);

    if (server.syslog_enabled) syslog(syslogLevelMap[level], "%s", msg);
}