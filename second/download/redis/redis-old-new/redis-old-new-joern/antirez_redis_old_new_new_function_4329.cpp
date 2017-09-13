static int selectDb(int fd)
{
    int retval;
    sds cmd;
    char type;

    if (config.dbnum == 0)
        return 0;

    cmd = sdsempty();
    cmd = sdscatprintf(cmd,"SELECT %d\r\n",config.dbnum);
    anetWrite(fd,cmd,sdslen(cmd));
    anetRead(fd,&type,1);
    if (type <= 0 || type != '+') return 1;
    retval = cliReadSingleLineReply(fd,1);
    if (retval) {
        close(fd);
	return retval;
    }
    return 0;
}