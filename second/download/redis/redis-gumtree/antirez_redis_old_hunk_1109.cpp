
    fclose(fp);
    stopLoading();
    return REDIS_OK;

eoferr: /* unexpected end of file is handled here with a fatal exit */
    serverLog(REDIS_WARNING,"Short read or OOM loading DB. Unrecoverable error, aborting now.");
    rdbExitReportCorruptRDB("Unexpected EOF reading RDB file");
    return REDIS_ERR; /* Just to avoid warning */
}

/* A background saving child (BGSAVE) terminated its work. Handle this.
