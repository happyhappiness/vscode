uint64_t RM_LoadUnsigned(RedisModuleIO *io) {
    if (io->ver == 2) {
        uint64_t opcode = rdbLoadLen(io->rio,NULL);
        if (opcode != RDB_MODULE_OPCODE_UINT) goto loaderr;
    }
    uint64_t value;
    int retval = rdbLoadLenByRef(io->rio, NULL, &value);
    if (retval == -1) goto loaderr;
    return value;

loaderr:
    moduleRDBLoadError(io);
    return 0; /* Never reached. */
}