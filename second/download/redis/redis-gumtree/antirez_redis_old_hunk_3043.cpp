            addReply(c,shared.ok);
        }
    }
    fclose(fp);
    close(fd);
    return;

file_wr_err:
    redisLog(REDIS_WARNING,"Can't write on tmp file for MIGRATE: %s",
        strerror(errno));
    addReplyErrorFormat(c,"MIGRATE failed, tmp file write error: %s.",
        strerror(errno));
    fclose(fp);
    close(fd);
    return;

file_rd_err:
    redisLog(REDIS_WARNING,"Can't read from tmp file for MIGRATE: %s",
        strerror(errno));
    addReplyErrorFormat(c,"MIGRATE failed, tmp file read error: %s.",
        strerror(errno));
    fclose(fp);
    close(fd);
    return;

