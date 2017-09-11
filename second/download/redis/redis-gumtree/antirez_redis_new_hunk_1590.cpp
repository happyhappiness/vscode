            /* advance position */
            positions[0] = positions[1];
        }
        zfree(entry.key);
    }

    /* because there is another potential error,
     * print how many valid ops we have processed */
    printValid(num_valid_ops, num_valid_bytes);

    /* expect an eof */
    if (entry.type != REDIS_RDB_OPCODE_EOF) {
        /* last byte should be EOF, add error */
        errors.level = 0;
        SHIFT_ERROR(positions[0].offset, "Expected EOF, got %s", types[entry.type]);
