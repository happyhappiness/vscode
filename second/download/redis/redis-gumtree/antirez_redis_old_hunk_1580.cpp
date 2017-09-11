    int dump_version;

    if (!readBytes(buf, 9)) {
        ERROR("Cannot read header\n");
    }

    /* expect the first 5 bytes to equal REDIS */
    if (memcmp(buf,"REDIS",5) != 0) {
        ERROR("Wrong signature in header\n");
    }

    dump_version = (int)strtol(buf + 5, NULL, 10);
    if (dump_version < 1 || dump_version > 6) {
        ERROR("Unknown RDB format version: %d\n", dump_version);
    }
    return dump_version;
}
