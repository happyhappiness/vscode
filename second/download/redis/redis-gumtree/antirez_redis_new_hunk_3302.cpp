        strerror(errno));
    fclose(fp);
    close(fd);
    return;

socket_wr_err:
    redisLog(REDIS_NOTICE,"Can't write to target node for MIGRATE: %s",
