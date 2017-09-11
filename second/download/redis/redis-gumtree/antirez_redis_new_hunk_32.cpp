/* In the context of the rdb_save method of a module data type, loads back the
 * float value saved by RedisModule_SaveFloat(). */
float RM_LoadFloat(RedisModuleIO *io) {
    if (io->ver == 2) {
        uint64_t opcode = rdbLoadLen(io->rio,NULL);
        if (opcode != RDB_MODULE_OPCODE_FLOAT) goto loaderr;
    }
    float value;
    int retval = rdbLoadBinaryFloatValue(io->rio, &value);
    if (retval == -1) goto loaderr;
    return value;

loaderr:
    moduleRDBLoadError(io);
    return 0; /* Never reached. */
}

/* --------------------------------------------------------------------------
