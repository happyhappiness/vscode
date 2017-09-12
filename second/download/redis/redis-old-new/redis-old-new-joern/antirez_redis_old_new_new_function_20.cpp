double RM_LoadDouble(RedisModuleIO *io) {
    if (io->ver == 2) {
        uint64_t opcode = rdbLoadLen(io->rio,NULL);
        if (opcode != RDB_MODULE_OPCODE_DOUBLE) goto loaderr;
    }
    double value;
    int retval = rdbLoadBinaryDoubleValue(io->rio, &value);
    if (retval == -1) goto loaderr;
    return value;

loaderr:
    moduleRDBLoadError(io);
    return 0; /* Never reached. */
}