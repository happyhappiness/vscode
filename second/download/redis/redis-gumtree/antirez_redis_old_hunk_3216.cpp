    time_t now = time(NULL);
    FILE *fp;
    char buf[64];

    if (level < server.verbosity) return;

    fp = (server.logfile == NULL) ? stdout : fopen(server.logfile,"a");
    if (!fp) return;

    strftime(buf,sizeof(buf),"%d %b %H:%M:%S",localtime(&now));
    fprintf(fp,"[%d] %s %c %s\n",(int)getpid(),buf,c[level],msg);
    fflush(fp);

    if (server.logfile) fclose(fp);
