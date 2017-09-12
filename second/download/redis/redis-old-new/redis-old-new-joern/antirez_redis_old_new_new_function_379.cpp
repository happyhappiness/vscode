double RM_LoadDouble(RedisModuleIO *io) {
    double value;
    int retval = rdbLoadBinaryDoubleValue(io->rio, &value);
    if (retval == -1) {
        moduleRDBLoadError(io);
        return 0; /* Never reached. */
    }
    return value;
}