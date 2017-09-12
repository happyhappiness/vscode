        if (buf == NULL) return NULL;
#endif
        buf[buflen-2] = '\0';
        va_start(ap, fmt);
        vsnprintf(buf, buflen, fmt, ap);
        va_end(ap);
        if (buf[buflen-2] != '\0') {
            zfree(buf);
            buflen *= 2;
