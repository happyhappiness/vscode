        server.master->authenticated = 1;
        server.replstate = REDIS_REPL_CONNECTED;
        redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
    }
}

int syncWithMaster(void) {
    char buf[1024], tmpfile[256], authcmd[1024];
    int fd = anetTcpConnect(NULL,server.masterhost,server.masterport);
    int dfd, maxtries = 5;

    if (fd == -1) {
        redisLog(REDIS_WARNING,"Unable to connect to MASTER: %s",
            strerror(errno));
        return REDIS_ERR;
    }

    /* AUTH with the master if required. */
    if(server.masterauth) {
    	snprintf(authcmd, 1024, "AUTH %s\r\n", server.masterauth);
    	if (syncWrite(fd, authcmd, strlen(server.masterauth)+7, 5) == -1) {
            close(fd);
            redisLog(REDIS_WARNING,"Unable to AUTH to MASTER: %s",
                strerror(errno));
            return REDIS_ERR;
    	}
        /* Read the AUTH result.  */
        if (syncReadLine(fd,buf,1024,3600) == -1) {
            close(fd);
            redisLog(REDIS_WARNING,"I/O error reading auth result from MASTER: %s",
                strerror(errno));
            return REDIS_ERR;
        }
        if (buf[0] != '+') {
            close(fd);
            redisLog(REDIS_WARNING,"Cannot AUTH to MASTER, is the masterauth password correct?");
            return REDIS_ERR;
        }
    }

    /* Issue the SYNC command */
    if (syncWrite(fd,"SYNC \r\n",7,5) == -1) {
        close(fd);
        redisLog(REDIS_WARNING,"I/O error writing to MASTER: %s",
            strerror(errno));
        return REDIS_ERR;
    }

    /* Prepare a suitable temp file for bulk transfer */
