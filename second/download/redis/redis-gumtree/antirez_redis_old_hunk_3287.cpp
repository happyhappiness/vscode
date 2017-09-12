
int clusterLoadConfig(char *filename) {
    FILE *fp = fopen(filename,"r");
   
    return REDIS_ERR;
    if (fp == NULL) return REDIS_ERR;
    fclose(fp);

    redisLog(REDIS_NOTICE,"Node configuration loaded, I'm %.40s",
        server.cluster.myself->name);
    return REDIS_OK;
