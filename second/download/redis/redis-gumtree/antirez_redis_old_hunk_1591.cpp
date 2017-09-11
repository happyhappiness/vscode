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
