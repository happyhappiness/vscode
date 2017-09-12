void clusterGetRandomName(char *p) {
    FILE *fp = fopen("/dev/urandom","r");
    char *charset = "0123456789abcdef";
    int j;

    if (!fp) {
        redisLog(REDIS_WARNING,
            "Unrecovarable error: can't open /dev/urandom:%s" ,strerror(errno));
        exit(1);
    }
    fread(p,REDIS_CLUSTER_NAMELEN,1,fp);
    for (j = 0; j < REDIS_CLUSTER_NAMELEN; j++)
        p[j] = charset[p[j] & 0x0F];
    fclose(fp);
}