        strerror(errno));
    fclose(fp);
    close(fd);

socket_rd_err:
    redisLog(REDIS_NOTICE,"Can't read from target node for MIGRATE: %s",
