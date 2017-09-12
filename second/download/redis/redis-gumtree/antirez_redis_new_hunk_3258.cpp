    char *charset = "0123456789abcdef";
    int j;

    if (fp == NULL || fread(p,REDIS_CLUSTER_NAMELEN,1,fp) == 0) {
        for (j = 0; j < REDIS_CLUSTER_NAMELEN; j++)
            p[j] = rand();
    }
    for (j = 0; j < REDIS_CLUSTER_NAMELEN; j++)
        p[j] = charset[p[j] & 0x0F];
    fclose(fp);
