void Close() {
        if (log) {
            fclose(log);
            log = NULL;
        }
    }