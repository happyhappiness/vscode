    sendto_flags |= MSG_NOSIGNAL;
#endif
    if (sendmsg(fd, &hdr, sendto_flags) < 0) {
        redisLog(REDIS_WARNING, "Can't send notification to systemd");
        close(fd);
        return 0;
    }
