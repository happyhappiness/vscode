    printValid(num_valid_ops, num_valid_bytes);

    /* expect an eof */
    if (entry.type != RDB_OPCODE_EOF) {
        /* last byte should be EOF, add error */
        errors.level = 0;
        SHIFT_ERROR(positions[0].offset, "Expected EOF, got %s", types[entry.type]);
