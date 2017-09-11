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
