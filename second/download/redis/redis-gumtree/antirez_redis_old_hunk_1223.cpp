    return REDIS_OK;

fmterr:
    redisLog(REDIS_WARNING,
        "Unrecoverable error: corrupted cluster config file.");
    zfree(line);
    if (fp) fclose(fp);
