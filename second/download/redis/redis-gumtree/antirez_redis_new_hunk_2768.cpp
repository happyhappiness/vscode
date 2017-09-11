    }

    dump_version = (int)strtol(buf + 5, NULL, 10);
    if (dump_version < 1 || dump_version > 4) {
        ERROR("Unknown RDB format version: %d\n", dump_version);
    }
    return 1;
