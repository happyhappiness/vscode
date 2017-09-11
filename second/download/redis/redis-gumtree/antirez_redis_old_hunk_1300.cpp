        len--;
        v++;
        if (b-buf == 64 || len == 0) {
            redisLogRaw(level|REDIS_LOG_RAW,buf);
            b = buf;
        }
    }
    redisLogRaw(level|REDIS_LOG_RAW,"\n");
}

/* =========================== Software Watchdog ============================ */
