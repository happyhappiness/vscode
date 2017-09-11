
int peekType() {
    unsigned char t;
    if (readBytes(&t, -1) && (t <= 4 || (t >=9 && t <= 12) || t >= 253))
        return t;
    return -1;
}

/* discard time, just consume the bytes */
int processTime() {
    uint32_t offset = CURR_OFFSET;
    unsigned char t[4];
    if (readBytes(t, 4)) {
        return 1;
    } else {
        SHIFT_ERROR(offset, "Could not read time");
