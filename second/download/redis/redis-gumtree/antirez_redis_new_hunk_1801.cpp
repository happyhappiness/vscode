        close(slave->repldbfd);
        slave->repldbfd = -1;
        aeDeleteFileEvent(server.el,slave->fd,AE_WRITABLE);
        putSlaveOnline(slave);
        redisLog(REDIS_NOTICE,"Synchronization with slave succeeded (disk)");
    }
}

