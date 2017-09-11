    }

    offset[1] = CURR_OFFSET;
    if (e.type == RDB_OPCODE_SELECTDB) {
        if ((length = loadLength(NULL)) == RDB_LENERR) {
            SHIFT_ERROR(offset[1], "Error reading database number");
            return e;
        }
        if (length > 63) {
            SHIFT_ERROR(offset[1], "Database number out of range (%d)", length);
            return e;
        }
    } else if (e.type == RDB_OPCODE_EOF) {
        if (positions[level].offset < positions[level].size) {
            SHIFT_ERROR(offset[0], "Unexpected EOF");
        } else {
