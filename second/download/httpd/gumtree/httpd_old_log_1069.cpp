fprintf(stderr,
                "to httpd.conf. The generated name will be /some/where.nnnn "
                "where nnnn is the\nsystem time at which the log nominally "
                "starts (N.B. this time will always be a\nmultiple of the "
                "rotation time, so you can synchronize cron scripts with it).\n"
                "At the end of each rotation time a new log is started.\n");