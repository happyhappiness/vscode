            return e;
        }
        if (length > 63) {
            SHIFT_ERROR(offset[1], "Database number out of range (%llu)", length);
            return e;
        }
    } else if (e.type == RDB_OPCODE_EOF) {
