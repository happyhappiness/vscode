/* In the context of the rdb_save method of a module data type, loads back the
 * double value saved by RedisModule_SaveDouble(). */
double RM_LoadDouble(RedisModuleIO *io) {
    double value;
    int retval = rdbLoadBinaryDoubleValue(io->rio, &value);
    if (retval == -1) {
        moduleRDBLoadError(io);
        return 0; /* Never reached. */
    }
    return value;
}

/* In the context of the rdb_save method of a module data type, saves a float 
 * value to the RDB file. The float can be a valid number, a NaN or infinity.
 * It is possible to load back the value with RedisModule_LoadFloat(). */
void RM_SaveFloat(RedisModuleIO *io, float value) {
    if (io->error) return;
    int retval = rdbSaveBinaryFloatValue(io->rio, value);
    if (retval == -1) {
        io->error = 1;
    } else {
