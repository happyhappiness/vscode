         * it exists, because we reference it with "oldfd". */
        latencyStartMonitor(latency);
        if (rename(tmpfile,server.aof_filename) == -1) {
            serverLog(LL_WARNING,
                "Error trying to rename the temporary AOF file: %s", strerror(errno));
            close(newfd);
            if (oldfd != -1) close(oldfd);
