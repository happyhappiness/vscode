    /* Limit offset to SIZE_T_MAX or 1GB in bytes */
    if ((loffset < 0) ||
        ((unsigned long long)loffset >= (unsigned)SIZE_T_MAX) ||
        ((unsigned long long)loffset >> 3) >= (1024*1024*1024))
    {
        addReplyError(c,err);
        return REDIS_ERR;
