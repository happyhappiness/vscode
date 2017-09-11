        len--;
        v++;
        if (b-buf == 64 || len == 0) {
            serverLogRaw(level|REDIS_LOG_RAW,buf);
            b = buf;
        }
    }
    serverLogRaw(level|REDIS_LOG_RAW,"\n");
}

/* =========================== Software Watchdog ============================ */
