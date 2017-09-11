        for (i = 0; i < length; i++) {
            offset = CURR_OFFSET;
            if (!processStringObject(NULL)) {
                SHIFT_ERROR(offset, "Error reading element at index %llu (length: %llu)",
                    (unsigned long long) i, (unsigned long long) length);
                return 0;
            }
        }
