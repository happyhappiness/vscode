static void syncCommand(redisClient *c) {
    struct stat sb;
    int fd = -1, len;
    time_t start = time(NULL);
    char sizebuf[32];

    redisLog(REDIS_NOTICE,"Slave ask for syncronization");
    if (flushClientOutput(c) == REDIS_ERR || saveDb(server.dbfilename) != REDIS_OK)
        goto closeconn;

    fd = open(server.dbfilename, O_RDONLY);
    if (fd == -1 || fstat(fd,&sb) == -1) goto closeconn;
    len = sb.st_size;

    snprintf(sizebuf,32,"%d\r\n",len);
    if (syncWrite(c->fd,sizebuf,strlen(sizebuf),5) == -1) goto closeconn;
    while(len) {
        char buf[1024];
        int nread;

        if (time(NULL)-start > REDIS_MAX_SYNC_TIME) goto closeconn;
        nread = read(fd,buf,1024);
        if (nread == -1) goto closeconn;
        len -= nread;
        if (syncWrite(c->fd,buf,nread,5) == -1) goto closeconn;
    }
    if (syncWrite(c->fd,"\r\n",2,5) == -1) goto closeconn;
    close(fd);
    c->flags |= REDIS_SLAVE;
    c->slaveseldb = 0;
    if (!listAddNodeTail(server.slaves,c)) oom("listAddNodeTail");
    redisLog(REDIS_NOTICE,"Syncronization with slave succeeded");
    return;

closeconn:
    if (fd != -1) close(fd);
    c->flags |= REDIS_CLOSE;
    redisLog(REDIS_WARNING,"Syncronization with slave failed");
    return;
}