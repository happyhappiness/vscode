        strerror(errno));
    fclose(fp);
    close(fd);

file_rd_err:
    redisLog(REDIS_WARNING,"Can't read from tmp file for MIGRATE: %s",
