    /* Exclude the final checksum for RDB >= 5. Will be checked at the end. */
    if (dump_version >= 5) {
        if (positions[0].size < 8) {
            serverLog(LL_WARNING, "RDB version >= 5 but no room for checksum.");
            exit(1);
        }
        positions[0].size -= 8;
