    }
}

/* A background saving child (BGSAVE) terminated its work. Handle this. */
void backgroundSaveDoneHandler(int statloc) {
    int exitcode = WEXITSTATUS(statloc);
    int bysignal = WIFSIGNALED(statloc);

    if (!bysignal && exitcode == 0) {
        redisLog(REDIS_NOTICE,
            "Background saving terminated with success");
        server.dirty = 0;
        server.lastsave = time(NULL);
    } else if (!bysignal && exitcode != 0) {
        redisLog(REDIS_WARNING, "Background saving error");
    } else {
        redisLog(REDIS_WARNING,
            "Background saving terminated by signal");
        rdbRemoveTempFile(server.bgsavechildpid);
    }
    server.bgsavechildpid = -1;
    /* Possibly there are slaves waiting for a BGSAVE in order to be served
     * (the first stage of SYNC is a bulk transfer of dump.rdb) */
    updateSlavesWaitingBgsave(exitcode == 0 ? REDIS_OK : REDIS_ERR);
}

/* A background append only file rewriting (BGREWRITEAOF) terminated its work.
 * Handle this. */
void backgroundRewriteDoneHandler(int statloc) {
    int exitcode = WEXITSTATUS(statloc);
    int bysignal = WIFSIGNALED(statloc);

    if (!bysignal && exitcode == 0) {
        int fd;
        char tmpfile[256];

        redisLog(REDIS_NOTICE,
            "Background append only file rewriting terminated with success");
        /* Now it's time to flush the differences accumulated by the parent */
        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) server.bgrewritechildpid);
        fd = open(tmpfile,O_WRONLY|O_APPEND);
        if (fd == -1) {
            redisLog(REDIS_WARNING, "Not able to open the temp append only file produced by the child: %s", strerror(errno));
            goto cleanup;
        }
        /* Flush our data... */
        if (write(fd,server.bgrewritebuf,sdslen(server.bgrewritebuf)) !=
                (signed) sdslen(server.bgrewritebuf)) {
            redisLog(REDIS_WARNING, "Error or short write trying to flush the parent diff of the append log file in the child temp file: %s", strerror(errno));
            close(fd);
            goto cleanup;
        }
        redisLog(REDIS_WARNING,"Parent diff flushed into the new append log file with success");
        /* Now our work is to rename the temp file into the stable file. And
         * switch the file descriptor used by the server for append only. */
        if (rename(tmpfile,server.appendfilename) == -1) {
            redisLog(REDIS_WARNING,"Can't rename the temp append only file into the stable one: %s", strerror(errno));
            close(fd);
            goto cleanup;
        }
        /* Mission completed... almost */
        redisLog(REDIS_NOTICE,"Append only file successfully rewritten.");
        if (server.appendfd != -1) {
            /* If append only is actually enabled... */
            close(server.appendfd);
            server.appendfd = fd;
            fsync(fd);
            redisLog(REDIS_NOTICE,"The new append only file was selected for future appends.");
        } else {
            /* If append only is disabled we just generate a dump in this
             * format. Why not? */
            close(fd);
        }
    } else if (!bysignal && exitcode != 0) {
        redisLog(REDIS_WARNING, "Background append only file rewriting error");
    } else {
        redisLog(REDIS_WARNING,
            "Background append only file rewriting terminated by signal");
    }
cleanup:
    sdsfree(server.bgrewritebuf);
    server.bgrewritebuf = sdsempty();
    aofRemoveTempFile(server.bgrewritechildpid);
    server.bgrewritechildpid = -1;
}

static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
    int j, loops = server.cronloops++;
    REDIS_NOTUSED(eventLoop);
