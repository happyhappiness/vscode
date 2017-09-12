static char* loadStringObject() {
    uint64_t offset = CURR_OFFSET;
    uint64_t len;
    int isencoded;

    len = loadLength(&isencoded);
    if (isencoded) {
        switch(len) {
        case RDB_ENC_INT8:
        case RDB_ENC_INT16:
        case RDB_ENC_INT32:
            return loadIntegerObject(len);
        case RDB_ENC_LZF:
            return loadLzfStringObject();
        default:
            /* unknown encoding */
            SHIFT_ERROR(offset, "Unknown string encoding (0x%02llx)",
                (unsigned long long) len);
            return NULL;
        }
    }

    if (len == RDB_LENERR) return NULL;

    char *buf = zmalloc(sizeof(char) * (len+1));
    if (buf == NULL) return NULL;
    buf[len] = '\0';
    if (!readBytes(buf, len)) {
        zfree(buf);
        return NULL;
    }
    return buf;
}