    if (rawmode) {
        fprintf(fp,"%s",msg);
    } else {
        strftime(buf,sizeof(buf),"%d %b %H:%M:%S",localtime(&now));
        fprintf(fp,"[%d] %s %c %s\n",(int)getpid(),buf,c[level],msg);
    }
    fflush(fp);
