static entry loadEntry() {
    entry e = { NULL, -1, 0 };
    uint64_t length, offset[4];

    /* reset error container */
    errors.level = 0;

    offset[0] = CURR_OFFSET;
    if (!loadType(&e)) {
        return e;
    }

    offset[1] = CURR_OFFSET;
    if (e.type == RDB_OPCODE_SELECTDB) {
        if ((length = loadLength(NULL)) == RDB_LENERR) {
            SHIFT_ERROR(offset[1], "Error reading database number");
            return e;
        }
        if (length > 63) {
            SHIFT_ERROR(offset[1], "Database number out of range (%llu)", length);
            return e;
        }
    } else if (e.type == RDB_OPCODE_EOF) {
        if (positions[level].offset < positions[level].size) {
            SHIFT_ERROR(offset[0], "Unexpected EOF");
        } else {
            e.success = 1;
        }
        return e;
    } else {
        /* optionally consume expire */
        if (e.type == RDB_OPCODE_EXPIRETIME ||
            e.type == RDB_OPCODE_EXPIRETIME_MS) {
            if (!processTime(e.type)) return e;
            if (!loadType(&e)) return e;
        }

        offset[1] = CURR_OFFSET;
        if (!loadPair(&e)) {
            SHIFT_ERROR(offset[1], "Error for type %s", types[e.type]);
            return e;
        }
    }

    /* all entries are followed by a valid type:
     * e.g. a new entry, SELECTDB, EXPIRE, EOF */
    offset[2] = CURR_OFFSET;
    if (peekType() == -1) {
        SHIFT_ERROR(offset[2], "Followed by invalid type");
        SHIFT_ERROR(offset[0], "Error for type %s", types[e.type]);
        e.success = 0;
    } else {
        e.success = 1;
    }

    return e;
}