        for (i = 0; i < length; i++) {
            offset = CURR_OFFSET;
            if (!processStringObject(NULL)) {
                SHIFT_ERROR(offset, "Error reading element key at index %d (length: %d)", i, length);
                return 0;
            }
            offset = CURR_OFFSET;
            if (!processStringObject(NULL)) {
                SHIFT_ERROR(offset, "Error reading element value at index %d (length: %d)", i, length);
                return 0;
            }
        }
