    sz = sizeof(dbuf);
    va_start(ap, msg);
    x = vsnprintf(dbuf, sz, msg, ap);
    va_end(ap);
    if (x > 0) {
        dbuf[x] = '\0';
        ++x;
        fputs(dbuf, stdout);
        *(dbuf) = '\0';
    } else {
        /* FAIL */
        debug("local_printfx() FAILURE: %" PRIuSIZE "\n", x);
    }
