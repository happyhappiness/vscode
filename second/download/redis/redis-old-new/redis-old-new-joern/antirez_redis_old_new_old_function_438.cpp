static char* loadStringObject() {
    uint32_t offset = CURR_OFFSET;
    int isencoded;
    uint32_t len;

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
            SHIFT_ERROR(offset, "Unknown string encoding (0x%02x)", len);
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