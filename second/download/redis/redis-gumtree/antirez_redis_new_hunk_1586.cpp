            SHIFT_ERROR(offset[1], "Database number out of range (%d)", length);
            return e;
        }
    } else if (e.type == REDIS_RDB_OPCODE_EOF) {
        if (positions[level].offset < positions[level].size) {
            SHIFT_ERROR(offset[0], "Unexpected EOF");
        } else {
