int dsOpen(void) {
    struct stat sb;
    int retval;
    char *path = server.ds_path;

    if ((retval = stat(path,&sb) == -1) && errno != ENOENT) {
        redisLog(REDIS_WARNING, "Error opening disk store at %s: %s",
                path, strerror(errno));
        return REDIS_ERR;
    }

    /* Directory already in place. Assume everything is ok. */
    if (retval == 0 && S_ISDIR(sb.st_mode)) return REDIS_OK;

    /* File exists but it's not a directory */
    if (retval == 0 && !S_ISDIR(sb.st_mode)) {
        redisLog(REDIS_WARNING,"Disk store at %s is not a directory", path);
        return REDIS_ERR;
    }

    /* New disk store, create the directory structure now, as creating
     * them in a lazy way is not a good idea, after very few insertions
     * we'll need most of the 65536 directories anyway. */
    if (mkdir(path,0644) == -1) {
        redisLog(REDIS_WARNING,"Disk store init failed creating dir %s: %s",
            path, strerror(errno));
        return REDIS_ERR;
    }
    return REDIS_OK;
}