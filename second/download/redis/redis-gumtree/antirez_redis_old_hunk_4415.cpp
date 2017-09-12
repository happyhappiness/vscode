            strerror(errno));
        return REDIS_ERR;
    }
    /* Issue the SYNC command */
    if (syncWrite(fd,"SYNC \r\n",7,5) == -1) {
        close(fd);
