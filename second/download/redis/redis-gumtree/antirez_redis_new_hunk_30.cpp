
/* Implements RM_LoadString() and RM_LoadStringBuffer() */
void *moduleLoadString(RedisModuleIO *io, int plain, size_t *lenptr) {
    if (io->ver == 2) {
        uint64_t opcode = rdbLoadLen(io->rio,NULL);
        if (opcode != RDB_MODULE_OPCODE_STRING) goto loaderr;
    }
    void *s = rdbGenericLoadStringObject(io->rio,
              plain ? RDB_LOAD_PLAIN : RDB_LOAD_NONE, lenptr);
    if (s == NULL) goto loaderr;
    return s;

loaderr:
    moduleRDBLoadError(io);
    return NULL; /* Never reached. */
}

/* In the context of the rdb_load method of a module data type, loads a string
