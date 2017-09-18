                "be a multiple of the rotation time, so you can synchronize\n"
                "cron scripts with it). At the end of each rotation time or "
                "when the file size\nis reached a new log is started.\n");
        exit(1);
    }

    szLogRoot = argv[argFile];

    ptr = strchr(argv[argIntv], 'M');
    if (ptr) {
        if (*(ptr+1) == '\0') {
            sRotation = atoi(argv[argIntv]) * 1048576;
        }
        if (sRotation == 0) {
            fprintf(stderr, "Invalid rotation size parameter\n");
            exit(1);
        }
    }
    else {
        if (argc >= (argBase + 4)) {
            utc_offset = atoi(argv[argOffset]) * 60;
        }
        tRotation = atoi(argv[argIntv]);
        if (tRotation <= 0) {
            fprintf(stderr, "Rotation time must be > 0\n");
            exit(6);
        }
    }

