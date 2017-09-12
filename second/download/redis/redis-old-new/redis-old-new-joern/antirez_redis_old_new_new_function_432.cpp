void *moduleLoadString(RedisModuleIO *io, int plain, size_t *lenptr) {
    void *s = rdbGenericLoadStringObject(io->rio,
              plain ? RDB_LOAD_PLAIN : RDB_LOAD_NONE, lenptr);
    if (s == NULL) {
        moduleRDBLoadError(io);
        return NULL; /* Never reached. */
    }
    return s;
}