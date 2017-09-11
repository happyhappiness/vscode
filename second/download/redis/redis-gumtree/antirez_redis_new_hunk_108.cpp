
    if (prefix != NULL)
        len = snprintf(buf,sizeof(buf),"%s: ",prefix);
    __redis_strerror_r(errno, (char *)(buf + len), sizeof(buf) - len);
    __redisSetError(c,type,buf);
}

