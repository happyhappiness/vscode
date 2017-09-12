    time_t now = time(NULL);
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
        strftime(buf,sizeof(buf),"%d %b %H:%M:%S",localtime(&now));
        fprintf(fp,"[%d] %s %c %s\n",(int)getpid(),buf,c[level],msg);
    }
    fflush(fp);

    if (server.logfile) fclose(fp);
