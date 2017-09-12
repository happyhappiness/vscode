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
