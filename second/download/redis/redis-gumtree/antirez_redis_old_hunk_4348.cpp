werr:
    fclose(fp);
    unlink(tmpfile);
    redisLog(REDIS_WARNING,"Write error writing append only fileon disk: %s", strerror(errno));
    if (di) dictReleaseIterator(di);
    return REDIS_ERR;
}
