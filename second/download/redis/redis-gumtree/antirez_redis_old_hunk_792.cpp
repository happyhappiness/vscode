    return C_OK;

fmterr:
    serverLog(REDIS_WARNING,
        "Unrecoverable error: corrupted cluster config file.");
    zfree(line);
    if (fp) fclose(fp);
