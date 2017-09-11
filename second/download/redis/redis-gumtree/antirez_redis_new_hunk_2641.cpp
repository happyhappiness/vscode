
int peekType() {
    unsigned char t;
    if (readBytes(&t, -1) && (checkType(t)))
        return t;
    return -1;
}

/* discard time, just consume the bytes */
int processTime(int type) {
    uint32_t offset = CURR_OFFSET;
    unsigned char t[8];
    int timelen = (type == REDIS_EXPIRETIME_MS) ? 8 : 4;

    if (readBytes(t,timelen)) {
        return 1;
    } else {
        SHIFT_ERROR(offset, "Could not read time");
