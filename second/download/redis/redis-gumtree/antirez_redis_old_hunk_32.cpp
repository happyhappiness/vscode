/* In the context of the rdb_save method of a module data type, loads back the
 * float value saved by RedisModule_SaveFloat(). */
float RM_LoadFloat(RedisModuleIO *io) {
    float value;
    int retval = rdbLoadBinaryFloatValue(io->rio, &value);
    if (retval == -1) {
        moduleRDBLoadError(io);
        return 0; /* Never reached. */
    }
    return value;
}

/* --------------------------------------------------------------------------
