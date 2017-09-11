/* In the context of the rdb_save method of a module data type, loads back the
 * double value saved by RedisModule_SaveDouble(). */
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

/* In the context of the rdb_save method of a module data type, saves a float
 * value to the RDB file. The float can be a valid number, a NaN or infinity.
 * It is possible to load back the value with RedisModule_LoadFloat(). */
void RM_SaveFloat(RedisModuleIO *io, float value) {
    if (io->error) return;
    int retval = rdbSaveLen(io->rio, RDB_MODULE_OPCODE_FLOAT);
    if (retval != -1) retval = rdbSaveBinaryFloatValue(io->rio, value);
    if (retval == -1) {
        io->error = 1;
    } else {
