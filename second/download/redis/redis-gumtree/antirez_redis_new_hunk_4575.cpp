    if (fd == -1 || fstat(fd,&sb) == -1) goto closeconn;
    len = sb.st_size;

    snprintf(sizebuf,32,"$%d\r\n",len);
    if (syncWrite(c->fd,sizebuf,strlen(sizebuf),5) == -1) goto closeconn;
    while(len) {
        char buf[1024];
