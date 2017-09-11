        if (crc != crc2) {
            SHIFT_ERROR(positions[0].offset, "RDB CRC64 does not match.");
        } else {
            serverLog(LL_WARNING, "CRC64 checksum is OK");
        }
    }

    /* print summary on errors */
    if (num_errors) {
        serverLog(LL_WARNING, "Total unprocessable opcodes: %llu",
            (unsigned long long) num_errors);
    }
}
