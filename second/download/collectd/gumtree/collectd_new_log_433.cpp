fprintf(stderr, "log_logstash plugin: fopen (%s) failed: %s\n",
            (log_file == NULL) ? DEFAULT_LOGFILE : log_file,
            sstrerror(errno, errbuf, sizeof(errbuf)));