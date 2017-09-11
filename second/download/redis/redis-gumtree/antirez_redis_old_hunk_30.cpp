
/* Implements RM_LoadString() and RM_LoadStringBuffer() */
void *moduleLoadString(RedisModuleIO *io, int plain, size_t *lenptr) {
    void *s = rdbGenericLoadStringObject(io->rio,
              plain ? RDB_LOAD_PLAIN : RDB_LOAD_NONE, lenptr);
    if (s == NULL) {
        moduleRDBLoadError(io);
        return NULL; /* Never reached. */
    }
    return s;
}

/* In the context of the rdb_load method of a module data type, loads a string
