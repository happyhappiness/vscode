void process() {
    uint64_t num_errors = 0, num_valid_ops = 0, num_valid_bytes = 0;
    entry entry;
    int dump_version = processHeader();

    /* Exclude the final checksum for RDB >= 5. Will be checked at the end. */
    if (dump_version >= 5) {
        if (positions[0].size < 8) {
            printf("RDB version >= 5 but no room for checksum.\n");
            exit(1);
        }
        positions[0].size -= 8;;
    }

    level = 1;
    while(positions[0].offset < positions[0].size) {
        positions[1] = positions[0];

        entry = loadEntry();
        if (!entry.success) {
            printValid(num_valid_ops, num_valid_bytes);
            printErrorStack(&entry);
            num_errors++;
            num_valid_ops = 0;
            num_valid_bytes = 0;

            /* search for next valid entry */
            uint64_t offset = positions[0].offset + 1;
            int i = 0;

            while (!entry.success && offset < positions[0].size) {
                positions[1].offset = offset;

                /* find 3 consecutive valid entries */
                for (i = 0; i < 3; i++) {
                    entry = loadEntry();
                    if (!entry.success) break;
                }
                /* check if we found 3 consecutive valid entries */
                if (i < 3) {
                    offset++;
                }
            }

            /* print how many bytes we have skipped to find a new valid opcode */
            if (offset < positions[0].size) {
                printSkipped(offset - positions[0].offset, offset);
            }

            positions[0].offset = offset;
        } else {
            num_valid_ops++;
            num_valid_bytes += positions[1].offset - positions[0].offset;

            /* advance position */
            positions[0] = positions[1];
        }
        free(entry.key);
    }

    /* because there is another potential error,
     * print how many valid ops we have processed */
    printValid(num_valid_ops, num_valid_bytes);

    /* expect an eof */
    if (entry.type != REDIS_EOF) {
        /* last byte should be EOF, add error */
        errors.level = 0;
        SHIFT_ERROR(positions[0].offset, "Expected EOF, got %s", types[entry.type]);

        /* this is an EOF error so reset type */
        entry.type = -1;
        printErrorStack(&entry);

        num_errors++;
    }

    /* Verify checksum */
    if (dump_version >= 5) {
        uint64_t crc = crc64(0,positions[0].data,positions[0].size);
        uint64_t crc2;
        unsigned char *p = (unsigned char*)positions[0].data+positions[0].size;
        crc2 = ((uint64_t)p[0] << 0) |
               ((uint64_t)p[1] << 8) |
               ((uint64_t)p[2] << 16) |
               ((uint64_t)p[3] << 24) |
               ((uint64_t)p[4] << 32) |
               ((uint64_t)p[5] << 40) |
               ((uint64_t)p[6] << 48) |
               ((uint64_t)p[7] << 56);
        if (crc != crc2) {
            SHIFT_ERROR(positions[0].offset, "RDB CRC64 does not match.");
        } else {
            printf("CRC64 checksum is OK\n");
        }
    }

    /* print summary on errors */
    if (num_errors) {
        printf("\n");
        printf("Total unprocessable opcodes: %llu\n",
            (unsigned long long) num_errors);
    }
}