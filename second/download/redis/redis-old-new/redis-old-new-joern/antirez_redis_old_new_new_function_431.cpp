uint64_t RM_LoadUnsigned(RedisModuleIO *io) {
    uint64_t value;
    int retval = rdbLoadLenByRef(io->rio, NULL, &value);
    if (retval == -1) {
        moduleRDBLoadError(io);
        return 0; /* Never reached. */
    }
    return value;
}