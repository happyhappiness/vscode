 * be called in the context of the rdb_load method of modules implementing
 * new data types. */
uint64_t RM_LoadUnsigned(RedisModuleIO *io) {
    uint64_t value;
    int retval = rdbLoadLenByRef(io->rio, NULL, &value);
    if (retval == -1) {
        moduleRDBLoadError(io);
        return 0; /* Never reached. */
    }
    return value;
}

/* Like RedisModule_SaveUnsigned() but for signed 64 bit values. */
