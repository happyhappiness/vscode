void dsFlushDb(int dbid) {
    char buf[1024];
    int j, i;

    redisLog(REDIS_NOTICE,"Flushing diskstore DB (%d)",dbid);
    for (j = 0; j < 256; j++) {
        for (i = 0; i < 256; i++) {
            snprintf(buf,1024,"%s/%02x/%02x",server.ds_path,j,i);
            dsFlushOneDir(buf,dbid);
        }
    }
}