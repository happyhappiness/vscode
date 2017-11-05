fprintf(stderr,
            "to httpd.conf. The generated name will be /some/where.nnnn "
            "where nnnn is the\nsystem time at which the log nominally "
            "starts (N.B. if using a rotation time,\nthe time will always "
            "be a multiple of the rotation time, so you can synchronize\n"
            "cron scripts with it). At the end of each rotation time or "
            "when the file size\nis reached a new log is started. If the "
            "-t option is specified, the specified\nfile will be truncated "
            "instead of rotated, and is useful where tail is used to\n"
            "process logs in real time.  If the -L option is specified, "
            "a hard link will be\nmade from the current log file to the "
            "specified filename.\n");