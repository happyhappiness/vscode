int clusterLoadConfig(char *filename) {
    FILE *fp = fopen(filename,"r");
    char *line;
    int maxline;
   
    if (fp == NULL) return REDIS_ERR;

    /* Parse the file. Note that single liens of the cluster config file can
     * be really long as they include all the hash slots of the node.
     * This means in the worst possible case REDIS_CLUSTER_SLOTS/2 integers.
     * To simplify we allocate 1024+REDIS_CLUSTER_SLOTS*16 bytes per line. */
    maxline = 1024+REDIS_CLUSTER_SLOTS*16;
    line = zmalloc(maxline);
    while(fgets(line,maxline,fp) != NULL) {
        int argc;
        sds *argv = sdssplitargs(line,&argc);

        printf("Node: %s\n", argv[0]);

        sdssplitargs_free(argv,argc);
    }
    zfree(line);
    fclose(fp);

    /* Config sanity check */
    /* TODO: check that myself is set. */
    return REDIS_ERR;

    redisLog(REDIS_NOTICE,"Node configuration loaded, I'm %.40s",
        server.cluster.myself->name);
    return REDIS_OK;

fmterr:
    redisLog(REDIS_WARNING,"Unrecovarable error: corrupted cluster config file.");
    fclose(fp);
    exit(1);
}